#
#/********************************************************************20**
#
#     Name:    SIP 
#
#     Type:    Python File
#
#     Desc:    
#
#     File:    cm_xta_cmdmap.py
#
#     Sid:      cm_xta_cmdmap.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
#
#     Prg:      
#
#*********************************************************************21*/
#!/usr/bin/env python

import os

# Table to map high level SIP messages to corresponding APIs
cmdMappingDef = {

   "INVITE" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.conreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                   "SFP" : 'tapa.sot.proxyreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.conind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                   "SFP" : 'tapa.sot.proxyind',
                },

              ],

   "INVITE_R" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.conrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.concfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],

   "INVITE_R_P" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],

   "MODIFY" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.modreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.modind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

   "MODIFY_R" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.modrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.modcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],

   "MODIFY_R_P" : [
                "SOT_ET_INVITE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],

   "ACK" : [
                "SOT_ET_ACK",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.ackreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.ackind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

   "OPTIONS" : [
                "SOT_ET_OPTIONS",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

   "OPTIONS_R" : [
                "SOT_ET_OPTIONS",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimcfm',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],

   "BYE" : [
                "SOT_ET_BYE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.relreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.relind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

   "BYE_R" : [
                "SOT_ET_BYE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.relrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.relcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],


   "SIPREL" : [
                "SOT_ET_LOCAL_REL",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.relreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq', 
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.relind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.relind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.relind',# cm_xta_cmdmap_py_001.main_
                },

              ],

   "SIPREL_R" : [
                "SOT_ET_LOCAL_REL",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.relrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.relcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimcfm',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],


   "CANCEL" : [
                "SOT_ET_CANCEL",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cancelreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                   "SFP" : 'tapa.sot.proxyreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cancelind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                   "SFP" : 'tapa.sot.proxyind',
                },

              ],


   "CANCEL_R" : [
                "SOT_ET_CANCEL",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cancelrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cancelcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],

   "REGISTER" : [
                "SOT_ET_REGISTER",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "REGISTER_R" : [
                "SOT_ET_REGISTER",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],

   "REGISTER_R_P" : [
                "SOT_ET_REGISTER",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                   "SFP" : 'tapa.sot.proxyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                   "SFP" : 'tapa.sot.proxycfm',
                },

              ],



   "UNKNOWN" : [
                "SOT_ET_UNKNOWN",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "UNKNOWN_R" : [
                "SOT_ET_UNKNOWN",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "INFO" : [
                "SOT_ET_INFO",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "INFO_R" : [
                "SOT_ET_INFO",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "COMET" : [
                "SOT_ET_PRECON_MET",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "COMET_R" : [
                "SOT_ET_PRECON_MET",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "PRACK" : [
                "SOT_ET_PRACK",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "PRACK_R" : [
                "SOT_ET_PRACK",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimcfm',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "REFER" : [
                "SOT_ET_REFER",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "REFER_R" : [
                "SOT_ET_REFER",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimcfm',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "SUBSCRIBE" : [
                "SOT_ET_SUBSCRIBE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "SUBSCRIBE_R" : [
                "SOT_ET_SUBSCRIBE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "SUBSCRIBE_R_P" : [
                "SOT_ET_SUBSCRIBE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cnstreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cnstind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "NOTIFY" : [
                "SOT_ET_NOTIFY",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "NOTIFY_R" : [
                "SOT_ET_NOTIFY",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "MESSAGE" : [
                "SOT_ET_MESSAGE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "MESSAGE_R" : [
                "SOT_ET_MESSAGE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


   "UPDATE" : [
                "SOT_ET_UPDATE",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

   "UPDATE_R" : [
                "SOT_ET_UPDATE",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],

   "SIPAUDIT" : [
                "SOT_ET_AUDIT",
                "SO_SIPMESSAGE_AUDIT",

                # Send Def
                {
                   "UA"  : 'tapa.sot.auditreq',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.auditreq',
                   "CSP" : 'tapa.sot.auditreq',
                   "TSP" : 'tapa.sot.auditreq',
                   "PRX" : 'tapa.sot.auditreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.auditcfm',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.auditcfm',
                   "CSP" : 'tapa.sot.auditcfm',
                   "TSP" : 'tapa.sot.auditcfm',
                   "PRX" : 'tapa.sot.auditcfm',
                },

              ],

   "SIPREFRESH" : [
                "SOT_ET_REFRESH",
                "SO_SIPMESSAGE_REFRESH",

                # Send Def
                {
                   "UA"  : 'tapa.sot.refreshind',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.refreshind',
                   "CSP" : 'tapa.sot.refreshind',
                   "TSP" : 'tapa.sot.refreshind',
                   "PRX" : 'tapa.sot.refreshind',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.refreshind',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.refreshind',
                   "CSP" : 'tapa.sot.refreshind',
                   "TSP" : 'tapa.sot.refreshind',
                   "PRX" : 'tapa.sot.refreshind',
                },

              ],

   "SIPERROR" : [
                "SOT_ET_ERROR",
                "SO_SIPMESSAGE_ERROR",
                "SOT_ERR_AUDIT_IN_PROGRESS",

                # Send Def
                {
                   "UA"  : 'tapa.sot.errind',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.errind',
                   "CSP" : 'tapa.sot.errind',
                   "TSP" : 'tapa.sot.errind',
                   "PRX" : 'tapa.sot.errind',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.errind',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.errind',
                   "CSP" : 'tapa.sot.errind',
                   "TSP" : 'tapa.sot.errind',
                   "PRX" : 'tapa.sot.errind',
                },

              ],

   "SIPANY" : [
                "SOT_ET_INVALID",
                "SO_SIPMESSAGE_NONE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.any',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.any',
                   "CSP" : 'tapa.sot.any',
                   "TSP" : 'tapa.sot.any',
                   "PRX" : 'tapa.sot.any',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.any',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.any',
                   "CSP" : 'tapa.sot.any',
                   "TSP" : 'tapa.sot.any',
                   "PRX" : 'tapa.sot.any',
                },

              ],

   "SIPANYREQ" : [
                "SOT_ET_INVALID",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.anyreq',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.anyreq',
                   "CSP" : 'tapa.sot.anyreq',
                   "TSP" : 'tapa.sot.anyreq',
                   "PRX" : 'tapa.sot.anyreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.anyreq',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.anyreq',
                   "CSP" : 'tapa.sot.anyreq',
                   "TSP" : 'tapa.sot.anyreq',
                   "PRX" : 'tapa.sot.anyreq',
                },

              ],

   "SIPANYRSP" : [
                "SOT_ET_INVALID",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.anyrsp',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.anyrsp',
                   "CSP" : 'tapa.sot.anyrsp',
                   "TSP" : 'tapa.sot.anyrsp',
                   "PRX" : 'tapa.sot.anyrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.anyrsp',
                   "DUA" : 'tapa.invalid',
                   "DTUA" : 'tapa.invalid',
                   "DSUA" : 'tapa.invalid',
                   "SLP" : 'tapa.sot.anyrsp',
                   "CSP" : 'tapa.sot.anyrsp',
                   "TSP" : 'tapa.sot.anyrsp',
                   "PRX" : 'tapa.sot.anyrsp',
                },

              ],

 "PUBLISH" : [
                "SOT_ET_PUBLISH",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],

 "PUBLISH_R" : [
                "SOT_ET_PUBLISH",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.camrsp',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimrsp',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.camcfm',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimcfm',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],
   "CIMINFO" : [
                "SOT_ET_INFO",
                "SO_SIPMESSAGE_REQUEST",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyreq',
                   "TSP" : 'tapa.sot.transreq',
                   "PRX" : 'tapa.sot.transreq',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxyind',
                   "TSP" : 'tapa.sot.transind',
                   "PRX" : 'tapa.sot.transind',
                },

              ],


   "CIMINFO_R" : [
                "SOT_ET_INFO",
                "SO_SIPMESSAGE_RESPONSE",

                # Send Def
                {
                   "UA"  : 'tapa.sot.cimreq',
                   "DUA" : 'tapa.hit.udatind',
                   "DTUA" : 'tapa.hit.datind',
                   "DSUA" : 'tapa.sct.datind',
                   "SLP" : 'tapa.sot.cimreq',
                   "CSP" : 'tapa.sot.proxyrsp',
                   "TSP" : 'tapa.sot.transrsp',
                   "PRX" : 'tapa.sot.transrsp',
                },

                # Expect Def
                {
                   "UA"  : 'tapa.sot.cimind',
                   "DUA" : 'tapa.hit.udatreq',
                   "DTUA" : 'tapa.hit.udatreq',
                   "DSUA" : 'tapa.hit.udatreq',
                   "SLP" : 'tapa.sot.cimind',
                   "CSP" : 'tapa.sot.proxycfm',
                   "TSP" : 'tapa.sot.transcfm',
                   "PRX" : 'tapa.sot.transcfm',
                },

              ],


}





#/********************************************************************30**
#
#         End of file:     cm_xta_cmdmap.py@@/main/tenb_main_ccb/1 - Wed Jul 22 18:59:09 2015
#
#*********************************************************************31*/
#
#
#/********************************************************************40**
#
#        Notes:
#
#*********************************************************************41*/
#
#/********************************************************************50**
#
#*********************************************************************51*/
#
#
#            cm_xta_cmdmap_py_002.main_  rr

#/********************************************************************60**
#
#        Revision history:
#
#*********************************************************************61*/
#
#/********************************************************************90**
#
#     ver       pat    init                  description
#------------ -------- ---- ----------------------------------------------
#            cm_xta_cmdmap_py_001.main_  rr
#            cm_xta_cmdmap_py_002.main_  rr
#/main/4      ---      sy  1. Update of sid field
#/main/5      ---      sk       1. Updated for PSF-SIP 1.1 Release
#/main/6      ---        vg       1. Updated for SO_AUDIT_LCD feature
#*********************************************************************91*/

