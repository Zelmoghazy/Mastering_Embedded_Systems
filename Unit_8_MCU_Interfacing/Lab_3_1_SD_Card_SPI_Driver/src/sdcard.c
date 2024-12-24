#include "sdcard.h"

/*
    @brief: release the SPI bus
*/
sd_ret_t sd_deactivate_cs(sd_handle_t *h)
{
    gpio_write_pin(GPIO_A, GPIO_PIN_4, GPIO_LEVEL_HIGH);    // Deactivate slave select
    uint16 tx = 0xFF;
    spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
    return SD_OK;
}

/*
    @brief: select the SD card
*/
sd_ret_t sd_activate_cs(sd_handle_t *h)
{
    gpio_write_pin(GPIO_A, GPIO_PIN_4, GPIO_LEVEL_LOW);     // Activate slave select
 
    return SD_OK;
}

/*
    @brief: send dummy bytes for certain clock cycles
*/
sd_ret_t sd_spi_wait(sd_handle_t *h, size_t n)
{
    // write a dummy byte out to generate clock, then read data
    uint16 dummy = 0xFF;
    for(size_t i = 0; i < n; i++){
        spi_tx_rx_data(SPI1, h->spi_cfg, &dummy);
    }
    return SD_OK;
}


/*
    @brief: wait for a valid SD card response
    @note : send a 0xFF and get received byte, 
    until a valid response is detected.
*/
sd_ret_t sd_get_resp(sd_handle_t *h, uint32 timeout)
{
    uint32 start = GET_TICKS();
    uint16 tx = 0xFF;
    uint16 rx = 0;

    do 
    {
        if(timeout != NO_TIMEOUT)
        {
            if((GET_TICKS()-start)>timeout)
            {
                return SD_ERR;
            }
        }
        rx = spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
    }while(SD_DETECTING_RESP(rx));

    h->resp.r1.all = (uint8) rx;

    return  SD_OK;
}

/*
    @brief: check we get the expected response
*/
sd_ret_t sd_verify_resp(sd_handle_t *h, sd_response_t *req_resp)
{
    if(sd_get_resp(h, 20) == SD_ERR)
    {
        return SD_ERR;
    }
    if(h->resp.r1.all != req_resp->r1.all)
    {
        return SD_ERR;
    }

    return SD_OK;
}


/*
    @brief: wait for the card to be ready
    @note : Before a command can be send,
    the application should check if a 0xFF
    can be read, which indicates the card is ready.
*/
sd_ret_t sd_wait(sd_handle_t *h, uint32 timeout)
{
    uint32 start = GET_TICKS();

    // write a dummy byte out to generate clock, then read data
    uint16 tx = 0xFF;
    while(spi_tx_rx_data(SPI1, h->spi_cfg, &tx) != 0xFF)
    {
        if(timeout != NO_TIMEOUT)
        {
            if((GET_TICKS()-start)>timeout)
            {
                return SD_ERR;
            }
        }
    }
    return  SD_OK;
}

/*
    Read and write commands have data transfers associated with them.
    For Single Block Read, Single Block Write and Multiple Block Read:
        - First byte: Start Block : 0xFE
        - Rest depending on data block length
        - last two bytes : 16-bit CRC
*/
sd_ret_t sd_rec_data(sd_handle_t *h, uint8 *buf, uint16 len)
{
    sd_response_t resp = {
        .r1.all = 0xFE,      // initiation token
    };

    if(sd_verify_resp(h, &resp) == SD_ERR)
    {
        return SD_ERR;
    }

    uint16 tx = 0xFF;
    for(size_t i =0; i < len; i++)
    {
        buf[i] =  spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
    }
    // ignore CRC
    spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
    spi_tx_rx_data(SPI1, h->spi_cfg, &tx);

    return SD_OK;
}

sd_ret_t sd_tx_block(sd_handle_t *h, uint8 *buf, sd_command_t cmd)
{
    return SD_OK;
}

sd_ret_t sd_send_cmd(sd_handle_t *h, sd_command_t cmd)
{
    sd_deactivate_cs(h);

    sd_activate_cs(h);

    // Wait until the card is ready before sending a command
    if(sd_wait(h, 300) != SD_OK)
    {
        sd_deactivate_cs(h);
        return SD_ERR;
    }

    uint16_t header = (uint16)cmd.header.all;
    spi_tx_rx_data(SPI1, h->spi_cfg, &header);

    uint16 args_b1 = (uint16)cmd.args.bytes.b1;
    spi_tx_rx_data(SPI1, h->spi_cfg, &args_b1);
    uint16 args_b2 = (uint16)cmd.args.bytes.b2;
    spi_tx_rx_data(SPI1, h->spi_cfg, &args_b2);
    uint16 args_b3 = (uint16)cmd.args.bytes.b3;
    spi_tx_rx_data(SPI1, h->spi_cfg, &args_b3);
    uint16 args_b4 = (uint16)cmd.args.bytes.b4;
    spi_tx_rx_data(SPI1, h->spi_cfg, &args_b4);

    uint16 footer = (uint16)cmd.footer.all;
    spi_tx_rx_data(SPI1, h->spi_cfg, &footer);

    if(cmd.header.bits.cmd_idx == STOP_TRANSMISSION)
    {
        //Skip a stuff byte
        uint16 tx = 0xFF;
        spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
    }

    if(sd_get_resp(h, 30) != SD_OK){
        return SD_ERR;
    }

    return SD_OK;
}


sd_ret_t sd_init(sd_handle_t *h)
{
    sd_ret_t ret = SD_ERR;
    h->card_type = SD_TYPE_ERR;

    uint8 buf[4]; 
    uint16 tx = 0xFF;

    enum {
        SD_POWERUP = 0,
        SD_SPI_INIT,
        SD_IDENT_V1,
        SD_IDENT_V2,
        SD_READY,
        SD_ERROR
    } init_stage = SD_POWERUP;

    for(;;)
    {
        switch(init_stage)
        {
            case SD_POWERUP:
                DELAY_MS(2);

                /*
                    Host provides at least 74 Clocks
                    before issuing first command
                    with CS high
                */
                sd_deactivate_cs(h);
                sd_spi_wait(h, 10);     // 80 Clocks

                init_stage = SD_SPI_INIT;
                break;

            case SD_SPI_INIT:
                /*
                    reset cmd to switch the card to SPI mode,
                    detect whether we are in idle state and
                    ready for initialization
                    send until a valid response is received
                    succeed when response = 0x1
                */

                do{
                    sd_send_cmd(h, SD_GET_CMD_0());
                }
                while(!SD_CHECK_RESP_IDLE(h->resp));

                /*
                    - After the host issues a reset command (CMD0) to reset the card, 
                      the host shall issue CMD8 prior to ACMD41 to re-initialize 
                      the SD Memory card.
                    - (ACMD41) is used to start initialization 
                      and to check if the card has completed initialization.
                    - It is mandatory to issue CMD8 prior to the first ACMD41.
                */

    
                if(sd_send_cmd(h, SD_GET_CMD_8()) != SD_OK)
                {
                    init_stage = SD_ERROR;
                    break;
                }

                // if sd card is legacy it will return illegal command
                if(SD_CHECK_RESP_ILLEGAL_CMD(h->resp))
                {
                    init_stage = SD_IDENT_V1;
                    break;
                }

                for(size_t i = 0; i < 4; i++){
                    buf[i] = (uint8)spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
                }

                /*
                    - CMD8 is used to verify SD Memory Card interface operating condition
                    - If the card can operate on the supplied voltage, the response echoes
                      back the supply voltage and the check pattern that were set in the 
                      command argument.
                */

                if(buf[2] == 0x01 && buf[3] == 0xAA)
                {
                    init_stage = SD_IDENT_V2;
                }
                else
                {
                    // unusable card (non compatible voltage range or check pattern error)
                    init_stage = SD_ERROR;
                }
                break;

            case SD_IDENT_V2:
                /*
                    repeat until it succeeds
                */
                do{
                    sd_send_cmd(h, SD_GET_CMD_55());
                    sd_send_cmd(h, SD_GET_ACMD_41());
                }             
                while(!SD_CHECK_RESP_SUCCESS(h->resp));

                /*
                    - This command requests the contents of the operating 
                      conditions register for the connected card.
                    - This response token is sent by the card when a 
                      READ_OCR command is received.
                */
                do{
                    sd_send_cmd(h, SD_GET_CMD_58());
                }
                while(!SD_CHECK_RESP_SUCCESS(h->resp));

                /*
                    The other four bytes contain the OCR register.
                */
                for(size_t i=0; i<4; i++){
                    buf[i] = (uint8)spi_tx_rx_data(SPI1, h->spi_cfg, &tx);
                }

                // Enhanced capacity detection
                if(!(buf[0] & 0x80)) {
                    init_stage = SD_ERROR;
                    break;
                }

                // Check "Card Capacity Status (CCS)", bit 30 which is only valid
                // if the "Card power up status bit", bit 31 is set.
                if(buf[0] & 0x40)
                {
                    h->card_type = SD_TYPE_V2_HC;  
                }
                else
                {
                    h->card_type = SD_TYPE_V2_SC;  
                }

                init_stage = SD_READY;
                break;

            case SD_IDENT_V1:
                sd_send_cmd(h, SD_GET_CMD_55());
                sd_send_cmd(h, SD_GET_ACMD_41());

                if(h->resp.r1.all <= 1)
                {
                    h->card_type = SD_TYPE_V1_SC;

                    do{
                        sd_send_cmd(h, SD_GET_CMD_55());
                        sd_send_cmd(h, SD_GET_ACMD_41());
                    }             
                    while(!SD_CHECK_RESP_SUCCESS(h->resp));  
                }
                else
                {
                    h->card_type = SD_TYPE_MMC;
                    do{
                        sd_send_cmd(h, SD_GET_CMD_1());
                    }             
                    while(!SD_CHECK_RESP_SUCCESS(h->resp));
                }

                sd_send_cmd(h, SD_GET_CMD_1());
                if(!SD_CHECK_RESP_SUCCESS(h->resp))
                {
                    init_stage = SD_ERROR;
                    break;
                }

                init_stage = SD_READY;
                break;

            case SD_READY:
                // Set blocksize (512)
                do{
                    sd_send_cmd(h, SD_GET_CMD_16());
                }
                while(!SD_CHECK_RESP_SUCCESS(h->resp));
                ret = SD_OK;
                break;

            case SD_ERROR:
                ret = SD_ERR;
                break;
        }

        sd_deactivate_cs(h);
        return ret;
    }
}

sd_ret_t sd_get_csd(sd_handle_t *h, uint8* csd_buf)
{
    sd_ret_t ret = SD_OK;

    sd_send_cmd(h, SD_GET_CMD_9());

    if(SD_CHECK_RESP_SUCCESS(h->resp))
    {
        ret  = sd_rec_data(h,csd_buf,16);
    }

    return ret;
}