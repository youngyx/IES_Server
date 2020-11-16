/** 
 * @file	IES.h
 * @brief	iFLY IES Header File
 * 
 *  This file contains the application programming interface (API) declarations 
 *  of IESNLP. Developer can iIESNLPlude this file in your project to build applications.
 *  For more information, please read the developer guide.
 **  Use of this software is subject to certain restrictions and limitations set
 *  forth in a license agreement entered into between iFLYTEK, Co,LTD.
 *  and the licensee of this software.  Please refer to the license
 *  agreement for license use rights and restrictions.
 *
 *  Copyright (C)    1999 - 2017 by ANHUI USTC iFLYTEK, Co,LTD.
 *                   All rights reserved.
 * 
 * @author  Speech Dept. iFLYTEK.
 * @version 1.0
 * @date    2017/07/15
 * 
 * @see        
 * 
 * History:
 * index    version        date            author        notes
 * 0        1.0           2017/07/15       IES		Create  file
 * 
 */


#ifndef __IES_H_2017_07_15__
#define __IES_H_2017_07_15__

#ifdef __cplusplus
extern "C" {
#endif /* C++ */

#ifdef WIN32
#define IESAPI	__stdcall
#else
#define IESAPI
#endif

/* Handles */
typedef void* HMRLSESSION;

/** 
 * @fn       IESAPIInit
 * @brief    IESAPI initialize.
 * 
 * @return   int - Return code, 0 to success.
 * @param    const char* config - [in] config file path .
 * @see        
 */
int IESAPI IESInit(const char* config);
typedef  int (IESAPI *Proc_IESInit)(const char* config);

/** 
 * @fn       IESCreate
 * @brief    IESAPI create.
 * 
 * @return   int - Return code, 0 to success.
 * @param    HMRLSESSION* session  - [out] the new session id.
 * @param    const char* param  - [in] params, it is json style, eg: {"nbest":"", "encode":"",
 * "resourceType":""}
 * @see        
 */
int IESAPI IESCreate(HMRLSESSION* session, const char* params);
typedef  int (IESAPI *Proc_IESCreate)(HMRLSESSION* session, const char* params);

/** 
 * @fn       IESReset
 * @brief    IESAPI reset.
 * 
 * @return   int - Return code, 0 to success.
 * @param    HMRLSESSION sessionid  - [in] the session id.
 * @param    const char* param  - [in] params, it is json style, eg: {"nbest":"", "encode":"",
 * "resourceType":""}
 * @see        
 */
int IESAPI IESReset(HMRLSESSION sessionid, const char* params);
typedef  int (IESAPI *Proc_IESReset)(HMRLSESSION sessionid, const char* params);

/** 
 * @fn       IESInterpret
 * @brief    IES Interpretation process. 
 *  
 * @return   const char* rslt - Return the results by IES Interpreter 
 * @param    HMRLSESSION* sessionid  - [in] the session id.
 * @param    const char* sent   - [in] The news information want to be interpreted
 * @param    const char* param  - [in] params, it is json style, eg: {"nbest":"", "encode":""}
 * @param    const char* rst   - [in] the result of interpret
 * @see
 */
int IESAPI IESInterpret(HMRLSESSION sessionid, const char* sent, const char** rst, const char * params);
typedef int (IESAPI *Proc_IESInterpret)(HMRLSESSION sessionid, const char* sent, const char** rst, const char * params);


/** 
 * @fn       IESProcess
 * @brief    IES process. 
 * 
 * @param    const char* param  - [in] params, it is json style, eg: {"nbest":"", "encode":""}
 * @param    const char* sent   - [in] The news information want to be process
 * @param    HMRLSESSION* sessionid - [in] the session id.
 * @param    const char* rst   - [in] the result of process
 * @see
 */
int IESAPI IESProcess(HMRLSESSION sessionid, const char* sent, const char** rst, const char * params);
typedef int (IESAPI *Proc_IESProcess)(HMRLSESSION sessionid, const char* sent, const char** rst, const char * params);


/*
 * @fn       IESDestroy
 * @brief    IES destroy. 
 * 
 * @param    HMRLSESSION* sessionid  - [in] the session id.
 * @see
 */
int IESAPI IESDestroy(HMRLSESSION sessionid);
typedef int (IESAPI *Proc_IESDestroy)(HMRLSESSION sessionid);



/** 
* @fn       IESEnd
* @brief    IES finish
* 
* @return   int - Return code, 0 to success.
* @see
*/
int  IESAPI IESFini();
typedef int (IESAPI *Proc_IESFini)();

#ifdef __cplusplus
}
#endif /* C++ */

#endif /* __IES_H_2017_07_15__ */
