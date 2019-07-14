/*
 * GiGA IoTMakers version 1.0
 *
 *  Copyright (c) 2016 kt corp. All rights reserved.
 *
 *  This is a proprietary software of kt corp, and you may not use this file except in
 *  compliance with license agreement with kt corp. Any redistribution or use of this
 *  software, with or without modification shall be strictly prohibited without prior written
 *  approval of kt corp, and the copyright notice above does not evidence any actual or
 *  intended publication of such software.
 */

#ifndef IOTMAKERS_PKTHEAD_H
#define IOTMAKERS_PKTHEAD_H

#include "im_common.h"
#include "packet/head_ext.h"

#define IOTMAKERS_PROTOCOL_VER_MAJOR		1
#define IOTMAKERS_PROTOCOL_VER_MINOR		1

#define IOTMAKERS_DEF_HEAD_LEN			35

/*
 * ********************************************************************************
 * packet/comn.h
 * ********************************************************************************
 */

typedef enum {
	HdrType_BASIC				= 1
	, HdrType_LIGHT_WEIGHT		= 2
} HdrType;

typedef enum {
	MsgType_NONE				= 0
	, MsgType_REQUEST			= 1
	, MsgType_RESPONSE			= 2
	, MsgType_REPORT			= 3
} MsgType;

typedef enum {
	MsgExchPtrn_NONE			= 0
	, MsgExchPtrn_ONE_WAY		= 1
	, MsgExchPtrn_ONE_WAY_ACK	= 2
	, MsgExchPtrn_THREE_WAY		= 3
} MsgExchPtrn;

typedef enum {
	UseYn_NO					= 0
	, UseYn_YES					= 1
} UseYn;

typedef enum {
	EncdngType_USER_DEFINED		= 0x01
	, EncdngType_XML			= 0x02
	, EncdngType_JSON			= 0x03
	, EncdngType_GPB			= 0x10
	, EncdngType_THRIFT			= 0x11
	, EncdngType_AVRO			= 0x12
	, EncdngType_PCRE			= 0x13
} EncdngType;

typedef enum {
	EcodType_AES_128			= 0x01
	, EcodTypeAES_256			= 0x02
	, EcodType_DES_64			= 0x11
	, EcodType_DES_EDE_192		= 0x12
	, EcodType_SEED_128			= 0x21
	, EcodType_ARIA_128			= 0x31
	, EcodType_ARIA_192			= 0x32
	, EcodType_ARIA_256			= 0x33
} EcodType;

typedef enum {
	CmpreType_HUFFMAN = 1
	, CmpreType_RUN_LENGTH = 2
	, CmpreType_SHANNON_FANO = 3
} CmpreType;


typedef enum {
	MthdType_NONE							= 0
	/** �÷��� �� ����� ���� ��ȸ */
	, MthdType_VER_GWVER_RQT				= 111
	/** �ܺνý��� TCP �α���  */
	, MthdType_ATHN_LOGINATHN_EXTRSYS_TCP	= 212
	/** ��ġ TCP �α��� */
	, MthdType_ATHN_LOGINATHN_DEV_TCP		= 214
	/** �ܺνý��� TCP ä�� ���� */
	, MthdType_ATHN_COMMCHATHN_EXTRSYS_TCP	= 222
	/** ��ġ TCP ä�� ���� */
	, MthdType_ATHN_COMMCHATHN_DEV_TCP 		= 224
	/** KeepAlive TCP ä�� */
	, MthdType_KEEP_ALIVE_COMMCHATHN_TCP	= 231
	/** ���������� ��ȸ */
	, MthdType_INITA_DATATYPE_RETV			= 311
	/** �ܺνý������� ��ȸ */
	, MthdType_INITA_EXTRSYS_RETV			= 321
	/** �ܺνý������� ���ź��� */
	, MthdType_INITA_EXTRSYS_UDATERPRT		= 322
	/** ��ġ���� ��ȸ */
	, MthdType_INITA_DEV_RETV				= 331
	/** ��ġ���� ���ź��� */
	, MthdType_INITA_DEV_UDATERPRT			= 332
	/** ��ġ���� ��ȸ(�÷���) */
	, MthdType_INITA_DEV_INFO				= 333
	/** �������� ���͸�������ȸ */
	, MthdType_COLEC_SETUP_FLTRCONDRETV		= 341
	/** �������� ���͸��������� */
	, MthdType_COLEC_SETUP_FLTRCONDTRMN		= 343
	/** �������� �̺�Ʈ������ȸ */
	, MthdType_COLEC_SETUP_EVCONDRETV		= 344
	/** �������� �̺�Ʈ�������� */
	, MthdType_COLEC_SETUP_EVCONDTRMN		= 346
	/** ���� ���յ����� */
	, MthdType_COLEC_ITGDATA_RECV			= 411
	/** ���� ���̵����� */
	, MthdType_COLEC_SNSNDATA_RECV			= 421
	/** ���� ��ġ������ */
	, MthdType_COLEC_LODATA_RECV			= 431
	/** ���� ���µ����� */
	, MthdType_COLEC_STTUSDATA_RECV			= 441
	/** ���� ���������� */
	, MthdType_COLEC_BINDATA_RECV			= 451
	/** ���� �̺�Ʈ */
	, MthdType_COLEC_EVDATA_RECV			= 461
	/** �ý������� �ǽð����� */
	, MthdType_CONTL_SYS_RTIMECONTL			= 511
	/** �ý������� �������� */
	, MthdType_CONTL_SYS_SETUPCHG			= 512
	/** ��ġ���� �ǽð����� */
	, MthdType_CONTL_DEV_RTIMECONTL			= 521
	/** ��ġ���� �������� */
	, MthdType_CONTL_DEV_SETUPCHG			= 522
	/** ��ġ���� �߿��������Ʈ */
	, MthdType_CONTL_DEV_FRMWRUDATE			= 523
	/** ���յ����� ���� */
	, MthdType_CONTL_ITGCNVY_DATA			= 525
	/** �ý������� üũ��Ŷ���� */
	, MthdType_CHK_SYS_CHKPACKTRCV			= 612
	/** ��ġ���� üũ��Ŷ���� */
	, MthdType_CHK_DEV_CHKPACKTRCV			= 622

	// (TODO)
	// �ӽ÷� �������...
	, MthdType_LAST_VAL_QUERY				= 711

	, MthdType_FRMWR_INFO					= 811
	, MthdType_FRMWR_UPDATE_NTFY			= 812
	, MthdType_FRMWR_UPDATE_STTUS_TRM		= 813
	, MthdType_FRMWR_DATA_TCP				= 816
	, MthdType_PKG_DATA_TCP					= 817
	,
} MthdType;

typedef enum {
	RespCd_NONE = 0
	/** ���� */
	, RespCd_NORMALITY = 100
	/** �Ϲݿ��� */
	, RespCd_GENERAL_ERROR = 200
	/** �������� */
	, RespCd_IMPLEMENTATION_ERROR = 201
	/** ��Ŷ Ǫ�� ���� */
	, RespCd_PACKET_PUSH_ERROR = 202
	/** ��ȣȭ ���� */
	, RespCd_DECRYPTION_ERROR = 203
	/** ��Ŷ�Ľ� ���� */
	, RespCd_PASSING_ERROR = 204
	/** ���� ���� */
	, RespCd_CERTIFICATION_ERROR = 205
	/** ���� ���� */
	, RespCd_ACK_ERROR = 206
	/** ���ä���������� */
	, RespCd_COMM_CH_ATHN_ERROR = 207
	/** ��û�������� */
	, RespCd_REQUEST_INFO_ERROR = 208
} RespCd;


/*
 * ********************************************************************************
 * �����ϴ� �޽������� ���������� ����ϴ� �޽����� �����Ѵ�.
 *
 * �߿��� �׸����δ� �޽������VO(IMPacketHead), �����ûVO(ComnReqVO), ��������VO(ComnRespVO), ���뺸��VO(ComnRprt) ���� �ִ�.
 * ���� �ֿ� �޽����� ������ �������� ���Ǵ� ������ ����ü(DevColecDataVO, SnsnDataInfoVO, StrDataInfoVO)���� �����Ѵ�.
 *
 * �������, ���� ���ռ���������VO�� �����Ϸ��� �Ѵٸ�
 * packet/400.h �� ���ǵ� ���ռ���������VO(ItgColecDataVO)�� �����ϰ�, �ش� VO���� ������������VO(DevColecDataVO)��
 * �߰��ϱ� ���ؼ��� packet/comn.h�� ���ǵ� �Լ����� ����ؾ� �Ѵ�.
 * ������������VO�� �ٸ� �޽��������� ���Ǵ� ����ü�̱� ������ packet/comn.h�� ���ǵǾ� �ִ�.
 * ********************************************************************************
 */

/*
 * �޽������VO(IMPacketHead)�� �����Ѵ�.
 * �޽�������� ��� �޽���(��û/����/����)�� ���������� ���ԵǴ� �⺻ �Ӽ��̴�.
 *
 * KTǥ������������ ������ [TCP Packet Length (4 Byte)] + [Message Header(35 Byte)] + [Message Body]�� �����Ǵµ�,
 * �޽������VO�� [Message Header]�� �ǹ��Ѵ�.
 *
 * �׸��� �޽������VO�� ���۵� ��, 35 Byte�� ��ȯ�Ǿ� ���۵ǰ�, (�޽������Ȯ��VO �����ϰ�, 35 Byte)

 0000: 00 00 00 87 11 01 00 23 | 60 e0 24 12 62 57 00 00 
 ..................==.==.=====...-====.,,,,,,,,,,,,,,,,,
 ................................msgType:2--MsgType_REQUEST(1) 01
 ................................msgExchPtrn:2--MsgExchPtrn_ONE_WAY_ACK(2) 10
 ................................methodType:12--MthdType_ATHN_COMMCHATHN_DEV_TCP(224)
 ................................01100000 1110000

60e0 :x86 0xFF0F (OK)
60e0 :mips(R) 0x0FFF (OK)
 */

#pragma pack(1)
typedef struct {
	unsigned char			protoMainVer:4;			// �������� ��������		(4bit)
	unsigned char			protoSubVer:4;			// �������� ��������		(4bit)
	unsigned char			hdrType;				// ���Ÿ��					(8bit)
	unsigned short			hdrLen;					// ��� ����				(16bit)
	// 4 bytes

	union ugly {
		unsigned char __pad [2];
#if defined(REVERSED)
		struct ugly2 {
			unsigned char	msgType:2;				// �޽��� ����				(�ֻ���2bit)
			unsigned char	msgExchPtrn:2;			// �޽��� ��ȯ ����			(����2bit)
			unsigned char	__dummy:4;
		}msgInfo;
#else
		struct ugly2 {
			unsigned char	__dummy:4;
			unsigned char	msgExchPtrn:2;			// �޽��� ��ȯ ����			(����2bit)
			unsigned char	msgType:2;				// �޽��� ����				(�ֻ���2bit)
		}msgInfo;
#endif
		unsigned short		methodType;				// �������					(����12bit)
	}ugly;
	// 2 bytes

	unsigned long long		trmTransacId;			// Ʈ����Ǿ��̵�			(64bit)
	// 8 bytes

	char					commChAthnNo[IOTMAKERS_STR_16_BYTE_LEN];		// ���ä��������ū	(128bit)
	// 16 bytes

	unsigned char			encryType:7;			// ��ȣȭ����				(����7bit)
	unsigned char			encryUsage:1;			// ��ȣȭ��뿩��			(����1bit)
	// 1 byte
	
	unsigned char			compType:7;				// ��������					(����7bit)
	unsigned char			compUsage:1;			// �����뿩��				(����1bit)
	// 1 byte
	
	unsigned char			encodType;				// ���ڵ�����				(8bit)
	// 1 byte
	
	unsigned short			rsltCd;					// ����ڵ�					(16bit)
	// 2 bytes
} IMHeadRaw, *IMHeadRawPtr;


#pragma pack(0)
typedef struct {
	IMHeadRaw	headRaw;
	IMHeadExt	ext;
	int			ext_cnt;	// ���Ȯ���ʵ��

} IMPacketHead, *IMPacketHeadPtr;


#ifdef __cplusplus
extern "C"
{
#endif

void im_pktHead_init(IMPacketHeadPtr head);
void im_pktHead_release(IMPacketHeadPtr head);

void im_pktHead_copy_trmTransacId(IMPacketHeadPtr headDest, IMPacketHeadPtr headSrc);

void im_pktHead_set_msgType(IMPacketHeadPtr head, MsgType type);
MsgType im_pktHead_get_msgType(IMPacketHeadPtr head);

void im_pktHead_set_msgExchPtrn(IMPacketHeadPtr head, MsgExchPtrn type);
MsgExchPtrn im_pktHead_get_msgExchPtrn(IMPacketHeadPtr head);

void im_pktHead_set_methodType(IMPacketHeadPtr head, MthdType type);
MthdType im_pktHead_get_methodType(IMPacketHeadPtr head);

void im_pktHead_set_trmTransacId(IMPacketHeadPtr head, unsigned long long trxid);
unsigned long long im_pktHead_get_trmTransacId(IMPacketHeadPtr head);

void im_pktHead_set_respCd(IMPacketHeadPtr head, RespCd rcode);
RespCd im_pktHead_get_respCd(IMPacketHeadPtr head);

void im_pktHead_set_hdrLen(IMPacketHeadPtr head, unsigned short len);
unsigned short im_pktHead_get_hdrLen(IMPacketHeadPtr head);

MthdType im_pktHead_look_MethType(char* recvBuf, int recvLen);
int im_pktHeadExt_get_count(IMPacketHeadPtr head);

int im_pktHeadExt_add_val(IMPacketHeadPtr head, char *key, char *val);
char* im_pktHeadExt_get_val(IMPacketHeadPtr head, char *key);

int im_pktHeadExt_get_serialized_to_buff(IMPacketHeadPtr head, char *o_buff, int o_buff_len) ;
int im_pktHeadExt_get_deserialize_from_buff(IMPacketHeadPtr head, char *buf) ;
int im_pktHead_get_serialized_to_buff(IMPacketHeadPtr head, char *o_buff, int o_buff_len);
int im_pktHead_get_deserialized_from_buff(IMPacketHeadPtr head, char* i_buff);
void im_pktHead_print(IMPacketHeadPtr head) ;

#ifdef __cplusplus
}
#endif






#endif

