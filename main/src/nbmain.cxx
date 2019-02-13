// @(#)root/main:$Id$
// Author: Enric Tejedor   07/10/15

/*************************************************************************
 * Copyright (C) 1995-2000, Rene Brun and Fons Rademakers.               *
 * All rights reserved.                                                  *
 *                                                                       *
 * For the licensing terms see $ROOTSYS/LICENSE.                         *
 * For the list of contributors see $ROOTSYS/README/CREDITS.             *
 *************************************************************************/

//////////////////////////////////////////////////////////////////////////
//                                                                      //
// NBMain                                                               //
//                                                                      //
// Main program used to spawn a ROOT notebook                           //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

#include "RConfigure.h"

#include "TCollection.h"
#include "TList.h"
#include "TROOT.h"
#include "TSystem.h"
#include "TSystemDirectory.h"
#include "TSystemFile.h"

#include <fstream>
#include <string>

#define JUPYTER_CMD        "jupyter"
#define NB_OPT             "notebook"
#define JUPYTER_CONF_DIR_V "JUPYTER_CONFIG_DIR"
#define JUPYTER_PATH_V     "JUPYTER_PATH"

using namespace std;

#ifdef WIN32
#include <process.h>
static string pathsep("\\");
#define execlp _execlp
#else
static string pathsep("/");
#endif

////////////////////////////////////////////////////////////////////////////////
/// Spawn a Jupyter notebook customised by ROOT.

int main()
{
   string rootsys(TROOT::GetRootSys().Data());

   // Set IPython directory for the ROOT notebook flavour
   string rootnbpath = rootsys + pathsep + 'etc' + pathsep + 'notebook';
   string jupyconfdir(JUPYTER_CONF_DIR_V + ("=" + rootnbpath));
   string jupypathdir(JUPYTER_PATH_V + ("=" + rootnbpath));
   putenv((char *)jupyconfdir.c_str());
   putenv((char *)jupypathdir.c_str());

   // Execute IPython notebook
   execlp(JUPYTER_CMD, JUPYTER_CMD, NB_OPT, NULL);

   // Exec failed
   fprintf(stderr,
           "Error starting ROOT notebook -- please check that Jupyter is installed\n");

   return 1;
}
