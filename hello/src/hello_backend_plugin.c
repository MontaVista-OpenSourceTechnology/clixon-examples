/*
 *
  ***** BEGIN LICENSE BLOCK *****
 
  Copyright (C) 2021-2022 Olof Hagsand and Rubicon Communications, LLC(Netgate)

  This file is part of CLIXON.

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

  Alternatively, the contents of this file may be used under the terms of
  the GNU General Public License Version 3 or later (the "GPL"),
  in which case the provisions of the GPL are applicable instead
  of those above. If you wish to allow use of your version of this file only
  under the terms of the GPL, and not to allow others to
  use your version of this file under the terms of Apache License version 2, indicate
  your decision by deleting the provisions above and replace them with the 
  notice and other provisions required by the GPL. If you do not delete
  the provisions above, a recipient may use your version of this file under
  the terms of any one of the Apache License version 2 or the GPL.

  ***** END LICENSE BLOCK *****
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>
#include <fcntl.h>
#include <sys/time.h>

/* clicon */
#include <cligen/cligen.h>

/* Clicon library functions. */
#include <clixon/clixon.h>

/* These include signatures for plugin and transaction callbacks. */
#include <clixon/clixon_backend.h> 

int hello_validate(clicon_handle h, transaction_data td) {
    cxobj **cxvec;
    size_t i, len;

    printf("*****hello validate*****\n");
    printf("src\n");
    xml_print(stdout, transaction_src(td));
    printf("target\n");
    xml_print(stdout, transaction_target(td));
    printf("dvec\n");
    cxvec = transaction_dvec(td);
    len = transaction_dlen(td);
    for (i = 0; i < len; i++) {
	printf(" [%lu] ", i);
	xml_print(stdout, cxvec[i]);
    }
    printf("avec\n");
    cxvec = transaction_avec(td);
    len = transaction_alen(td);
    for (i = 0; i < len; i++) {
	printf(" [%lu] ", i);
	xml_print(stdout, cxvec[i]);
    }
    printf("scvec\n");
    cxvec = transaction_scvec(td);
    len = transaction_clen(td);
    for (i = 0; i < len; i++) {
	printf(" [%lu] ", i);
	xml_print(stdout, cxvec[i]);
    }
    printf("tcvec\n");
    cxvec = transaction_tcvec(td);
    for (i = 0; i < len; i++) {
	printf(" [%lu] ", i);
	xml_print(stdout, cxvec[i]);
    }
    return 0;
}

int hello_commit(clicon_handle h, transaction_data td) {
    printf("*****hello commit*****\n");
    return 0;
}

/* Forward declaration */
clixon_plugin_api *clixon_plugin_init(clicon_handle h);

static clixon_plugin_api api = {
    "hello backend",
    clixon_plugin_init,
    .ca_trans_commit = hello_commit,
    .ca_trans_validate = hello_validate,
};

clixon_plugin_api *
clixon_plugin_init(clicon_handle h) {
    printf("*****hello init*****\n");
    return &api;
}
