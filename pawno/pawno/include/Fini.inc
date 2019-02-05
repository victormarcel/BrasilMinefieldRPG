/*////////////////////////////////////////////////////////////////////////////////

                     _ ____        _____          __  __
                    (_)  _ \ ___  |_   _|__  __ _|  \/  |
                    | | |_) / __|   | |/ _ \/ _` | |\/| |
                    | |  __/\__ \   | |  __/ (_| | |  | |
                    |_|_|   |___/   |_|\___|\__,_|_|  |_|

                        Intelligent Programming Style ®

                         ____________________________
[url]www.ips-team.blogspot.com[/url]
[url]www.ips-team.forumeiros.com[/url]
____________________________

Created By DraKiNs & SlashPT
Thanks to [iPs]TeaM and Jhony

*/
////////////////////////////////////////////////////////////////////////////////

//========= [ Configs of Read/Write Files ] ====================================

#define MaxLines    (999)
#define MaxKeys     (064)

#define Fini_GetBool(%0)    (bool:strval(Fini_GetStr(%0)))
#define Fini_GetValue(%0)   (strval(Fini_GetStr(%0)))
#define Fini_Exists(%0)     (fexist(%0))
#define Fini_GetFloat(%0)   floatstr(Fini_GetStr(%0))
#define Fini_Remove(%0)     (fremove(%0))

//========= [ Variables of Set/Get Ini ] ========================================

new
sCacheKeys[MaxLines][MaxKeys],
sCacheValue[MaxLines][MaxKeys],
iLoop           = 0x0,
iFind           = 0x0,
iKeySet         = 0x0,
File:iFile      = File:0,
sTemp[MaxKeys]  = " ";

//============ [ Functions ] ================================================

//Get ~ Read Functions
stock Fini_GetStr(sKey[])
{
    iLoop = 0x0;
    while((sCacheKeys[iLoop][0x0]) && (iLoop < MaxLines)) {
        if(!strcmp(sCacheKeys[iLoop],sKey,false))
            return sCacheValue[iLoop];
        ++iLoop;
    }
    return sCacheKeys[0];
}


//Others Funcions
stock   Fini_Create(sFile[])
{
    if(Fini_Exists(sFile)) return false;
    iFile = fopen(sFile,io_write);
    return fclose(iFile);
}


stock Fini_OpenFile(sFile[])
{
    iFile = fopen(sFile,io_read),
        iFind   = 0x0;
    iLoop = 0x0;

    while(fread(iFile,sTemp)) {
        sTemp[strlen(sTemp) - 2] = EOS;
        iFind   = strfind(sTemp,"=");
        format(sCacheValue[iLoop],MaxKeys,sTemp[iFind + 1]);
        sTemp[iFind] = EOS;
        format(sCacheKeys[iLoop],MaxKeys,sTemp);
        ++iLoop;
    }
    return fclose(iFile);
}


stock Fini_SaveFile(sFile[])
{
    iFile = fopen(sFile,io_write),
        sTemp[0] = EOS;

    iLoop = 0x0;
    while((sCacheKeys[iLoop][0x0]) && (iLoop < MaxLines)) {
        format(sTemp,MaxKeys,"%s=%s\r\n",sCacheKeys[iLoop],sCacheValue[iLoop]);
        fwrite(iFile,sTemp);
        ++iLoop;
    }
    return fclose(iFile);
}


stock Fini_CloseFile()
{
    sCacheKeys[0][0]    =   EOS;
    sCacheValue[0][0]   =   EOS;
    iLoop               =   0x0;
    iFind               =   0x0;
    iKeySet             =   0x0;
    sTemp[0]            =   EOS;
    return true;
}


stock Fini_IsSet(sTag[])
{
    iLoop = 0x0;
    while((sCacheKeys[iLoop][0x0]) && (iLoop < MaxLines)) {
        if(!strcmp(sCacheKeys[iLoop],sTag,false)) {
            return true;
        }
        iLoop++;
    }
    return false;
}


//Set ~ Write Functions

stock Fini_SetStr(sKey[],sValue[])
{
    iLoop = 0x0;
    while((sCacheKeys[iLoop][0x0]) && (iLoop < MaxLines)) {
        if(!strcmp(sCacheKeys[iLoop],sKey,false)) {
            sCacheValue[iLoop][0] = EOS;
            strcat(sCacheValue[iLoop],sValue);
            iKeySet = 1;
        }
        ++iLoop;
    }
    if(!iKeySet) {
        while(sCacheKeys[iLoop][0]) iLoop++;
        strcat(sCacheValue[iLoop],sValue);
        strcat(sCacheKeys[iLoop],sKey);
    }
    return EOS;
}


stock Fini_SetFloat(sTag[],Float:iVal)
{
    format(sTemp,MaxKeys,"%f",iVal);
    return Fini_SetStr(sTag,sTemp);
}


stock Fini_SetVal(sTag[],iVal)
{
    format(sTemp,MaxKeys,"%d",iVal);
    return Fini_SetStr(sTag,sTemp);
}


stock Fini_SetBool(sTag[],bool:iVal)
{
    format(sTemp,MaxKeys,"%d",iVal);
    return Fini_SetStr(sTag,sTemp);
}