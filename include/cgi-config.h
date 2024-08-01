//SPDX-License-Identifier: AGPL-3.0

/**
 * Copyright (C) 2024 - Ágatha Isabelle Chris Moreira Guedes
 *
 * Author: Ágatha Isabelle Chris Moreira Guedes <code@agatha.dev>
 * 
 * @file cgi-config.h
 * @description: defines/reads defined configuration macros
 * 
 * *********************************************************************
 *
 *                          L  I  C  E  N  S  E
 *
 * *********************************************************************
 * This code is licensed under the GNU Affero General Public License
 * version 3 <https://www.gnu.org/licenses/agpl-3.0.html>.
 *
 * This file is part of agatha-cgi-utils.
 *
 * agatha-cgi-utils is free software: you can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License
 * as published by the Free Software Foundation, in the version 3 of the
 * License.
 * 
 * agatha-cgi-utils is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Affero General Public License for more details.

 * You should have received a copy of the GNU Affero General Public
 * License along with agatha-cgi-utils. If not, see
 * <https://www.gnu.org/licenses/> and
 * <https://www.gnu.org/licenses/agpl-3.0.html>.
 * 
 **/

 #ifndef __CGI_CONFIG_H
 #define __CGI_CONFIG_H

#ifndef __PREFIX

#define __PREFIX "/srv/cgi"

#endif//__PREFIX

#ifndef __PKGDIR

#define __PKGDIR __PREFIX "/agatha-cgi-utils"

#endif//__PKGDIR

#ifndef __CFGDIR

#define __CFGDIR __PKGDIR "/etc"

#endif//__CFGDIR

#ifndef __DATADIR

#define __DATADIR __PKGDIR "/data"

#endif//__DATADIR

#ifndef __TMPDIR

#define __TMPDIR __DATADIR "/tmp"

#endif//__TMPDIR

#endif//__CGI_CONFIG_H