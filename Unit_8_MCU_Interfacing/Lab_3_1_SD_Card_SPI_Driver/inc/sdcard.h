
#ifndef SD_CARD_H_
#define SD_CARD_H_

#include "Platform_Types.h"
#include <spi.h>
#include "systick.h"


#define NO_TIMEOUT 0

#define GO_IDLE_STATE                 0
#define SEND_OP_COND                  1
#define SEND_IF_COND                  8
#define SEND_CSD                      9
#define SEND_CID                      10
#define STOP_TRANSMISSION             12
#define SET_BLOCKLEN                  16
#define READ_SINGLE_BLOCK             17
#define READ_MULTIPLE_BLOCK           18
#define SET_BLOCK_COUNT               23
#define WRITE_BLOCK                   24
#define WRITE_MULTIPLE_BLOCK          25
#define APP_CMD                       55
#define READ_OCR                      58
#define CRC_ON_OFF                    59

/*
    "ACMDxx" = application-specific command. 
    Send CMD55 to tell the SD card, 
    that the next command is an ACMD. 
*/
#define APP_SEND_OP_COND              41
#define SET_WR_BLOCK_ERASE_COUNT      23


/*
    Since CMD0 has no arguments, the content of 
    all the fields, including the CRC field, 
    are constants and need not be calculated in run time. 

    A valid reset command is:
        0x40, 0x0, 0x0, 0x0, 0x0, 0x95
*/

#define SD_GET_CMD_0()  (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx   = 0x0,\
                            .args.all = 0x0,\
                            .footer.all = 0x95,\
                        }

/*
    0x1 AA
        - 0x1  : support 2.7-3.6 V
        - 0xAA : AA common check pattern (can be anything else)
*/
#define SD_GET_CMD_8()  (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = SEND_IF_COND,\
                            .args.all = 0x1AA,\
                            .footer.all = 0x87,\
                        }

#define SD_GET_CMD_55() (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = APP_CMD,\
                            .args.all = 0x0,\
                            .footer.all = 0x65,\
                        }      

#define SD_GET_ACMD_41()(sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = APP_SEND_OP_COND,\
                            .args.all = 0x40000000,\
                            .footer.all = 0x77,\
                        }

#define SD_GET_CMD_58() (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = READ_OCR,\
                            .args.all = 0x0,\
                            .footer.all = 0xFD,\
                        }

#define SD_GET_CMD_1()  (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = 0x1,\
                            .args.all = 0x0,\
                            .footer.all = 0xF9,\
                        }

#define SD_GET_CMD_16() (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = SET_BLOCKLEN,\
                            .args.all = 512,\
                            .footer.all = 0x01,\
                        }

#define SD_GET_CMD_9() (sd_command_t){\
                            .header.bits.start_bit = 0x0,\
                            .header.bits.trans_bit = 0x1,\
                            .header.bits.cmd_idx = SEND_CSD,\
                            .args.all = 0,\
                            .footer.all = 0x01,\
                        }



/*
    The command is 48 bit (6 byte) long:
    - 1 byte command
    - 4 byte argument (often 0, so 0x00000000)
    - 1 byte of CRC7 + end bit.
*/

#pragma pack(1)
typedef struct sd_command_t 
{
    union{
        struct{
            uint8_t start_bit:1;
            uint8_t trans_bit:1;
            uint8_t cmd_idx:6;
        }bits;
        uint8_t all;
    }header;
    union {
        struct{
            uint8_t b1;
            uint8_t b2;
            uint8_t b3;
            uint8_t b4;
        }bytes;
        uint32_t all;
    }args;
    union{
        struct{
            uint8_t crc7 : 7;
            uint8_t end_bit : 1;
        }bits;
        uint8_t all;
    }footer;
}sd_command_t;

/* The MSB is always set to zero for any response. */
#define SD_DETECTING_RESP(r)          ((r) & (1<<7U))

/*
    There are some command response formats, R1, R2, R3 and R7
    depending on the command index. 
    A byte of response (R1), is returned for most commands. 
        - the value 0x00 means successful.
    - When any error occured, corresponding status bit 
      in the response will be set.
    - The R3/R7 response (R1 + trailing 32-bit data) 
      is for only CMD58 and CMD8.
*/
#define SD_CHECK_RESP_IDLE(r)         (r.r1.all == 0x1)
#define SD_CHECK_RESP_SUCCESS(r)      (r.r1.all == 0x0)
#define SD_CHECK_RESP_ILLEGAL_CMD(r)  ((r.r1.all & 0x05) != 0x0)

#pragma pack(1)
typedef struct sd_response_t
{
    union{
        struct{
            uint8_t idle:1;
            uint8_t erase_rst:1;
            uint8_t ill_cmd:1;
            uint8_t com_crc_err:1;
            uint8_t erase_seq_err:1;
            uint8_t addr_err:1;
            uint8_t param_err:1;
            uint8_t zeroed:1;
        }bits;
        uint8_t all;
    }r1;
    union {
        struct {
            uint32_t reserved1:15;
            uint32_t v27_28:1;        // Voltage window 2.7V-2.8V
            uint32_t v28_29:1;        // Voltage window 2.8V-2.9V
            uint32_t v29_30:1;        // Voltage window 2.9V-3.0V
            uint32_t v30_31:1;        // Voltage window 3.0V-3.1V
            uint32_t v31_32:1;        // Voltage window 3.1V-3.2V
            uint32_t v32_33:1;        // Voltage window 3.2V-3.3V
            uint32_t v33_34:1;        // Voltage window 3.3V-3.4V
            uint32_t v34_35:1;        // Voltage window 3.4V-3.5V
            uint32_t v35_36:1;        // Voltage window 3.5V-3.6V
            uint32_t switching_1v8:1; // Switching to 1.8V accepted
            uint32_t reserved2:2;
            uint32_t uhs2_status:1;   // UHS-II Card Status
            uint32_t ccs:1;           // Card Capacity Status
            uint32_t busy:1;          // Card power up status bit (busy)
        }ocr;
        struct{
            uint8_t cmd_ver;
            uint8_t reserved_bits;
            uint8_t voltage_accepted;
            uint8_t check_pattern_echo;
        }r7;
        uint8_t bytes[4];
    }data;
}sd_response_t;

typedef enum sd_type_t
{
    SD_TYPE_ERR,
    SD_TYPE_MMC,
    SD_TYPE_V1_SC,
    SD_TYPE_V2_SC,
    SD_TYPE_V2_HC
}sd_type_t;

typedef enum sd_err_t
{
    SD_ERR_NONE,
    SD_ERR_IDLE,
    SD_ERR_ERASE_RST,
    SD_ERR_ILL_CMD,
    SD_ERR_CRC,
    SD_ERR_ERASE_SEQ,
    SD_ERR_ADDR,
    SD_ERR_PARAM
}sd_err_t;

typedef enum sd_state_t
{
    SD_STATE_READY,
    SD_STATE_BUSY,
    SD_STATE_ERR,
    SD_STATE_TIMEOUT,
    SD_STATE_DONE
}sd_state_t;

typedef enum sd_mode_t
{
    SD_MODE_READING,
    SD_MODE_WRITING,
    SD_MODE_READY
}sd_mode_t;

typedef struct sd_handle_t {
    spi_config_t  *spi_cfg;
    sd_mode_t     mode;
    sd_err_t      err;
    sd_type_t     card_type;
    sd_response_t resp;
}sd_handle_t;

typedef enum sd_ret_t
{
    SD_OK,
    SD_ERR
}sd_ret_t;


sd_ret_t sd_deactivate_cs(sd_handle_t *h);
sd_ret_t sd_activate_cs(sd_handle_t *h);
sd_ret_t sd_spi_wait(sd_handle_t *h, size_t n);
sd_ret_t sd_get_resp(sd_handle_t *h, uint32 timeout);
sd_ret_t sd_verify_resp(sd_handle_t *h, sd_response_t *req_resp);
sd_ret_t sd_wait(sd_handle_t *h, uint32 timeout);
sd_ret_t sd_rec_data(sd_handle_t *h, uint8 *buf, uint16 len);
sd_ret_t sd_tx_block(sd_handle_t *h, uint8 *buf, sd_command_t cmd);
sd_ret_t sd_send_cmd(sd_handle_t *h, sd_command_t cmd);
sd_ret_t sd_get_csd(sd_handle_t *h, uint8* csd_buf);
sd_ret_t sd_init(sd_handle_t *h);

#endif