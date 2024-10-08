/*
 * YAFFS: Yet Another Flash File System. A NAND-flash specific file system.
 *
 * Copyright (C) 2002-2015 Aleph One Ltd.
 *
 * Created by Charles Manning <charles@aleph1.co.uk>
 *
 * This software is the subject of a Licence Agreement between Aleph One Limited and Hi_Silicon_Huawei_DigiMedia.
 *
 */

/*
 * Header file for using yaffs in an application via
 * a direct interface.
 */


#ifndef __YAFFSCFG_H__
#define __YAFFSCFG_H__


#include "yportenv.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#ifdef CONFIG_YAFFS_SMALL_RAM
#define YAFFSFS_N_HANDLES	10
#define YAFFSFS_N_DSC		2
#else
#define YAFFSFS_N_HANDLES	100
#define YAFFSFS_N_DSC		20
#endif


struct yaffsfs_DeviceConfiguration {
	const YCHAR *prefix;
	struct yaffs_dev *dev;
};


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* __YAFFSCFG_H__ */
