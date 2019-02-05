/*////////////////////////////////////////////////////////////////////////////////

                     _ ____        _____          __  __
                    (_)  _ \ ___  |_   _|__  __ _|  \/  |
                    | | |_) / __|   | |/ _ \/ _` | |\/| |
                    | |  __/\__ \   | |  __/ (_| | |  | |
                    |_|_|   |___/   |_|\___|\__,_|_|  |_|

                        Intelligent Programming Style ®

                        ____________________________
							www.ips-team.blogspot.com
							www.ips-team.forumeiros.com
						____________________________

					Created By DraKiNs & SlashPT
					Thanks to [iPs]TeaM and Jhony

					*/
////////////////////////////////////////////////////////////////////////////////

//========= [ Configs of Read/Write Files ] ====================================

#define MaxLines    (110)
#define MaxKeys     (064)

#define Fini_GetBool(%0)    (bool:strval(Fini_GetStr(%0)))
#define Fini_GetValue(%0)   (strval(Fini_GetStr(%0)))
#define Fini_Exists(%0)     (fexist(%0))
#define Fini_GetFloat(%0)   floatstr(Fini_GetStr(%0))
#define Fini_Remove(%0)     (fremove(%0))

#define WINDOWS 		//delete if no use windows

//========= [ Variables of Set/Get Ini ] ========================================

new
	sCacheKeys[MaxLines][MaxKeys],
	sCacheValue[MaxLines][MaxKeys],
	izLoopz_            			= 0x0,
	izFindsearch_       			= 0x0,
	izSetKeySet_        			= 0x0,
	File:izFileTag      			= File:0,
	szTempKeysVal[MaxKeys]  		= " ";

//============ [ Functions ] ================================================

//Get ~ Read Functions
stock Fini_GetStr(sKey[])
{
    izLoopz_ = 0x0;
    while((sCacheKeys[izLoopz_][0]) && (izLoopz_ < MaxLines))
	{
        if(!strcmp(sCacheKeys[izLoopz_],sKey,false))
        {
            return sCacheValue[izLoopz_];
		}
        ++izLoopz_;
    }
    return sCacheKeys[0];
}


//Others Funcions
stock Fini_Create(sFile[])
{
    if(Fini_Exists(sFile)) return false;
    izFileTag = fopen(sFile,io_write);
    return fclose(izFileTag);
}


stock Fini_OpenFile(sFile[])
{
    izFileTag = fopen(sFile,io_read),
	izFindsearch_   = 0;
    izLoopz_ = 0;

    while(fread(izFileTag,szTempKeysVal))
	{
        szTempKeysVal[strlen(szTempKeysVal) - 2] = EOS;
        izFindsearch_   = strfind(szTempKeysVal,"=");
        format(sCacheValue[izLoopz_],MaxKeys,szTempKeysVal[izFindsearch_ + 1]);
        szTempKeysVal[izFindsearch_] = EOS;
        format(sCacheKeys[izLoopz_],MaxKeys,szTempKeysVal);
        ++izLoopz_;
    }
    return fclose(izFileTag);
}


stock Fini_SaveFile(sFile[])
{
    izFileTag = fopen(sFile,io_write),
	szTempKeysVal[0] = EOS;
	
    izLoopz_ = 0x0;
    while((sCacheKeys[izLoopz_][0]) && (izLoopz_ < MaxLines)) {

	#if defined WINDOWS
        format(szTempKeysVal,MaxKeys,"%s=%s\r\n",sCacheKeys[izLoopz_],sCacheValue[izLoopz_]);
	#else
        format(szTempKeysVal,MaxKeys,"%s=%s\n",sCacheKeys[izLoopz_],sCacheValue[izLoopz_]);
	#endif
        fwrite(izFileTag,szTempKeysVal);
        ++izLoopz_;
    }
    return fclose(izFileTag);
}


stock Fini_PrintFile()
{
    izLoopz_ =0;
    while((sCacheKeys[izLoopz_][0x0]) && (izLoopz_ < MaxLines))
	{
	    printf("%s=%s",sCacheKeys[izLoopz_],sCacheValue[izLoopz_]);
    }
    return true;
}


stock Fini_CloseFile()
{
    sCacheKeys[0][0]    =   EOS;
    sCacheValue[0][0]   =   EOS;
    izLoopz_			=   0;
    izFindsearch_		=   0;
    izSetKeySet_  		=   0;
    szTempKeysVal[0]	=   EOS;
    return true;
}


stock Fini_IsSet(sTag[])
{
    izLoopz_ = 0x0;
    while((sCacheKeys[izLoopz_][0]) && (izLoopz_ < MaxLines))
	{
        if(!strcmp(sCacheKeys[izLoopz_],sTag,false))
        {
            return true;
        }
        izLoopz_++;
    }
    return false;
}


//Set ~ Write Functions

stock Fini_SetStr(sKey[],sValue[])
{
    izLoopz_ = 0x0;
    izSetKeySet_ = 0;
    while(strlen(sCacheKeys[izLoopz_]) > 1&& (izLoopz_ < MaxLines))
	{
        if(!strcmp(sCacheKeys[izLoopz_],sKey,false))
		{
            sCacheValue[izLoopz_][0] = EOS;
            strcat(sCacheValue[izLoopz_],sValue);
            izSetKeySet_ = 1;
        }
        ++izLoopz_;
    }
    if(!izSetKeySet_)
	{
        strcat(sCacheValue[izLoopz_],sValue);
        strcat(sCacheKeys[izLoopz_ ],sKey);
    }
    return EOS;
}


stock Fini_SetFloat(sTag[],Float:iVal)
{
    format(szTempKeysVal,MaxKeys,"%f",iVal);
    return Fini_SetStr(sTag,szTempKeysVal);
}


stock Fini_SetVal(sTag[],iVal)
{
    format(szTempKeysVal,MaxKeys,"%d",iVal);
    return Fini_SetStr(sTag,szTempKeysVal);
}


stock Fini_SetBool(sTag[],bool:iVal)
{
    format(szTempKeysVal,MaxKeys,"%d",iVal);
    return Fini_SetStr(sTag,szTempKeysVal);
}
