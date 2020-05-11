//***************************************************************************//
//* ��Ȩ����  www.mediapro.cc
//*
//* ����ժҪ��SDSrt-AVCom�ڲ�����ģʽ����DLL�ӿ�
//*	
//* ��ǰ�汾��V1.0		
//* ��    �ߣ�mediapro
//* ������ڣ�2020-3-6
//**************************************************************************//

#ifndef _SD_SRT_AVCOM_SDK_H_
#define _SD_SRT_AVCOM_SDK_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
#ifndef BUILDING_DLL
#define DLLIMPORT __declspec (dllexport)
#else /* Not BUILDING_DLL */
#define DLLIMPORT __declspec (dllimport)
#endif /* Not BUILDING_DLL */
#else
#define DLLIMPORT
#endif

#ifdef __APPLE__
#ifndef OBJC_BOOL_DEFINED
typedef int BOOL;
#endif 
#else
#ifndef BOOL
typedef int BOOL;
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif
#ifndef FALSE
#define FALSE 0
#endif

//��������JITTER ����ʱ��
#define MAX_SUPPORT_JITTER_MS		3000

//��־����ļ���
typedef enum LOG_OUTPUT_LEVEL
{
	LOG_OUTPUT_LEVEL_DEBUG = 1,
	LOG_OUTPUT_LEVEL_INFO,
	LOG_OUTPUT_LEVEL_WARNING,
	LOG_OUTPUT_LEVEL_ERROR,
	LOG_OUTPUT_LEVEL_ALARM,
	LOG_OUTPUT_LEVEL_FATAL,
	LOG_OUTPUT_LEVEL_NONE
} LOG_OUTPUT_LEVEL;

//2D FEC����ģʽ
typedef enum E_SRT_FEC_LAYOUT {
	//��ͨ����ģʽ
	e_SRT_FEC_LAYOUT_EVEN = 0,
	//����ģʽ�����Խ���һ�����ʲ������������ɢ���ͣ�
	e_SRT_FEC_LAYOUT_STAIR
}E_SRT_FEC_LAYOUT;


//FEC-ARQ���ģʽ
typedef enum E_SRT_FEC_ARQ {
	//ֻҪ�������ᷢ��ARQ������FEC�ܷ�ָ�
	e_SRT_FEC_ARQ_ALWAYS = 0,
	//����FECʧ��ʱ����ARQ
	e_SRT_FEC_ARQ_ONREQ,
	//�ر�ARQ
	e_SRT_FEC_ARQ_NEVER,
}E_SRT_FEC_ARQ;


//������յ�������Ƶ���� �ص�����
//bComplete������ʾ��ǰ֡�����Ƿ��������޾ֲ�������
//bPrevTotalFrameLost������ʾ��ǰ֡����һ�����֮֡������֡��ʧ�����������֡�������һ֡����Ƿ�������
//ͨ������������־����Ϲؼ�֡�ж���־�������Ժܷ����ʵ�ֶ�֡�������
typedef void (*CallBackFuncRecvVideoData)(void* pObj, int nLen, unsigned char *byBuf, unsigned int unPTS, BOOL bComplete, BOOL bPrevTotalFrameLost);

typedef void (*CallBackFuncRecvAudioData)(void* pObj, int nLen, unsigned char *byBuf, unsigned int unPTS);


//////////////////////////////////////////////////////////////////////////
// SrtAvCom�ӿ�

/***
* ������ʼ����ϵͳֻ�����һ�Σ���Ҫ����SRT�����Լ���־ģ��ĳ�ʼ��
* @param:outputPath��ʾ��־���·����֧�����·���;���·������Ŀ¼�����ڽ��Զ�����
* @param:outputPath��ʾ��־����ļ���ֻ�е��ڻ��߸��ڸü������־������ļ���ȡֵ��Χ�ο�LOG_OUTPUT_LEVEL
* @return: 
*/
DLLIMPORT void  SDSrtAvCom_Enviroment_Init(const char* outputPath, int outputLevel);

DLLIMPORT void  SDSrtAvCom_Enviroment_Free();

/***
* ����SrtAvCom
* @param unLogId: ��־ID����������־���ʱ�Ķ����ʶ��
* @return: ����ģ��ָ�룬ΪNULL��ʧ��
*/
DLLIMPORT void*  SDSrtAvCom_Create(UINT unLogId);

/***
* ����SrtAvCom��ʹ����Ӧ������������API֮��Ļ��Ᵽ��
* @param pRtp_avcom: ģ��ָ��
* @return:
*/
DLLIMPORT void  SDSrtAvCom_Delete(void* pRtp_avcom);


/***
* ��ʼ����
* @param strLocalIP: ����IP��ַ
* @param shLocalPort: �����շ��˿ڣ��ö˿�������Ƶ����Ƶ�˿ں��ڴ˻����ϼ�1��
* @param strRemoteIP: �Է�IP��ַ
* @param shRemotePort: �Է��շ��˿ڣ��ö˿�������Ƶ����Ƶ�˿ں��ڴ˻����ϼ�1��
* @param pfVideoRecvCallBack: ���յ��Է����͵���Ƶ���ݺ�Ļص�����
* @param pfAudioRecvCallBack: ���յ��Է����͵���Ƶ���ݺ�Ļص�����
* @param pObject: �������������ص�����ʱ�ĸ���͸���βΣ�ģ���ڲ������������������͸������
* @return: TRUE FALSE
*/
DLLIMPORT BOOL  SDSrtAvCom_Start(
	void* pRtp_avcom,
	const char *strLocalIP, 
	USHORT shLocalPort, 
	const char *strRemoteIP, 
	USHORT shRemotePort, 
	CallBackFuncRecvVideoData pfVideoRecvCallBack,
	CallBackFuncRecvAudioData pfAudioRecvCallBack,
	void *pObject);


/***
* ֹͣSrtAvCom����
* @param pRtp_avcom: ģ��ָ��
* @return:
*/
DLLIMPORT void  SDSrtAvCom_Stop(void* pRtp_avcom);

/***
* ������Ƶ����
* @param pRtp_avcom: ģ��ָ��
* @param byBuf: ����һ֡��Ƶ��������������ADTS���ڲ��޲��͸��
* @param nLen: ���ݳ���
* @return: 
*/
DLLIMPORT BOOL  SDSrtAvCom_SendAudioData(void* pRtp_avcom, unsigned char *byBuf, int nLen);

/***
* ������Ƶ����
* @param pRtp_avcom: ģ��ָ��
* @param byBuf: ����һ֡����ʼ������������ڲ����в��ƴ��
* @param nLen: ���ݳ���
* @return: 
*/
DLLIMPORT BOOL  SDSrtAvCom_SendVideoData(void* pRtp_avcom, unsigned char *byBuf, int nLen);


/***
* ���û����������������Start�ӿ�֮ǰ����
* @param pRtp_avcom: ģ��ָ��
* @param nRecvDelayMs: ���ջ���ʱ�䣬����4*RTT����λms�����ڷ��Ͷ˻���ն����ã���ȡ���нϴ��ֵ
* @param nMaxBitrateKbps����������ʣ�����2*VideoEncBitrate����λkbps����Ҫ�ڷ��Ͷ����ã�������Ϊ0ʱ��ʾ������
* @return:
*/
DLLIMPORT BOOL  SDSrtAvCom_SetBaseTransParams(void* pRtp_avcom, int nRecvDelayMs, int nMaxBitrateKbps);


/***
* ������Ƶͨ��FEC�������������Start�ӿ�֮ǰ����
* @param pRtp_avcom: ģ��ָ��
* @param bEnable: �Ƿ�����FEC���շ�˫���豣��һ��
* @param nCols: FEC Group����
* @param nRows: FEC Group����
* @param eLayoutMode��2D FEC����ģʽ
* @param eArqMode��FEC-ARQ���ģʽ
* @return:
*/
DLLIMPORT BOOL  SDSrtAvCom_SetVideoFecParams(void* pRtp_avcom, BOOL bEnable, int nCols, int nRows, E_SRT_FEC_LAYOUT eLayoutMode, E_SRT_FEC_ARQ eArqMode);



/***
* ������Ƶͨ��FEC�������������Start�ӿ�֮ǰ����
* @param pRtp_avcom: ģ��ָ��
* @param bEnable: �Ƿ�����FEC���շ�˫���豣��һ��
* @param nCols: FEC Group����
* @param nRows: FEC Group����
* @param eLayoutMode��2D FEC����ģʽ
* @param eArqMode��FEC-ARQ���ģʽ
* @return:
*/
DLLIMPORT BOOL  SDSrtAvCom_SetAudioFecParams(void* pRtp_avcom, BOOL bEnable, int nCols, int nRows, E_SRT_FEC_LAYOUT eLayoutMode, E_SRT_FEC_ARQ eArqMode);



/***
* ��ȡ��Ƶͨ��ͳ����Ϣ
* @param pRtp_avcom: ģ��ָ��
* @param pfRttMs: RTT����λ����
* @param pfUpLossRate: ���ж�����.�ڲ��Ѿ���100
* @param pfDownLossRate: ���ж�����.�ڲ��Ѿ���100
* @param pfEstimatedUpBitrate�����д������.Kbps
* @param pfUpBitrate����������.Kbps
* @param pfDownBitrate����������.Kbps
* @return:
*/
DLLIMPORT BOOL  SDSrtAvCom_GetVideoTransStatis(void* pRtp_avcom, double *pfRttMs, double *pfUpLossRate, double *pfDownLossRate, 
											double *pfEstimatedUpBitrate, double *pfUpBitrate, double *pfDownBitrate);


/***
* ��ȡ��Ƶͨ��ͳ����Ϣ
* @param pRtp_avcom: ģ��ָ��
* @param pfRttMs: RTT����λ����
* @param pfUpLossRate: ���ж�����.�ڲ��Ѿ���100
* @param pfDownLossRate: ���ж�����.�ڲ��Ѿ���100
* @param pfEstimatedUpBitrate�����д������.Kbps
* @param pfUpBitrate����������.Kbps
* @param pfDownBitrate����������.Kbps
* @return:
*/
DLLIMPORT BOOL  SDSrtAvCom_GetAudioTransStatis(void* pRtp_avcom, double *pfRttMs, double *pfUpLossRate, double *pfDownLossRate,
											double *pfEstimatedUpBitrate, double *pfUpBitrate, double *pfDownBitrate);
#ifdef __cplusplus
}
#endif

#endif // _SD_SRT_AVCOM_SDK_H_
