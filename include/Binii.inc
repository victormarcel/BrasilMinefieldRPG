////////////////////////////////////////////////////////////////////////////////
//
//
//        #### ########   ######     ######## ########    ###    ##     ##
//         ##  ##     ## ##    ##       ##    ##         ## ##   ###   ###
//         ##  ##     ## ##             ##    ##        ##   ##  #### ####
//         ##  ########   ######        ##    ######   ##     ## ## ### ##
//         ##  ##              ##       ##    ##       ######### ##     ##
//         ##  ##        ##    ##       ##    ##       ##     ## ##     ##
//        #### ##         ######        ##    ######## ##     ## ##     ##
//
//
//            Criado por Bruno da Silva (iPs DraKiNs) and [S]trong 
//                           Special thanks to Double-O-Seven
//
//          Acesse meu blog sobre programação www.ips-team.blogspot.com
//
//          [iPs]TeaM soluções de programação em geral (agora com cursos)
//
//          		www.ips-team.6te.net/smforum (contate-nos)
//
//              [iPs]Ini Files (pós fini 5.0) Versão 2.0 (ultra rápido)
//
//
/////////////////////////////////////////////////////////////////////////////////


// Funções Atuais:

//   CallBack INI_WriteString("key", "valor")
//   CallBack INI_WriteFloat("key", valor)
//   CallBack INI_WriteInt("key", valor)

//   CallBack INI_ReadString("key")
//   CallBack INI_ReadInt("key")
//   CallBack INI_ReadFloat("key")

//   CallBack INI_Create()
//   CallBack INI_Open("arquivo")

//   CallBack INI_Isset("tag")
//   CallBack INI_Print()

//   CallBack INI_Close()
//   CallBack INI_Save()

#pragma dynamic 45000 
#define MAX_LINES		999
#define MAX_CHARS	256

#define CallBack%0(%1)	stock %0(%1)
#define Variable%0<%1>      	static stock %0[%1]

#define INI_Isset(%0)			(INI_ReadInt(tagExists) == 0xFF)
#define strcpy(%0,%1,%2)		strcat((%0[0] = EOS, %0), %1, %2 + 1)

#define INI_ReadInt(%0)		strval(INI_ReadString(%0))
#define INI_ReadFloat(%0)	floatstr(INI_ReadString(%0))


Variable nomeKey		<MAX_LINES>[MAX_CHARS >>> 1];
Variable valorKey		<MAX_LINES>[MAX_CHARS >>> 1];
Variable valorNumerico	<MAX_LINES>;
Variable nomeArquivo	<MAX_CHARS / 2>;
new totalLinhas = 0;


//////////////////////////////////////////////////////////////////////////////

CallBack INI_Create(checarArquivo[])
{
	if(fexist(checarArquivo)) return false;

	new File:arquivoFopen = fopen(checarArquivo, io_append);

	return fclose(arquivoFopen), true;
}

////////////////////////////////////////////////////////////////////////////////

static stringTemporariaRetornar[MAX_CHARS / 2] = "255";

CallBack INI_ReadString(keyGet[])
{
	new i = 0, valorGetNumerico = INI_HashString(keyGet);


	for(i = 0;  i != totalLinhas ; ++i) if(valorGetNumerico == valorNumerico[i])
	{
		if(strcmp(nomeKey[i], keyGet, false)) continue;

		return valorKey[i];
	}	
	return stringTemporariaRetornar;
}
///////////////////////
stock INI_Remove(const filename[])
{
	if (!filename[0]) return false;
	return fremove(filename);
}

////////////////////////////////////////////////////////////////////////////////
CallBack INI_Open(arquivoLer[])
{
	if((strlen(nomeKey[0]) || strlen(valorKey[0]))) INI_Save(), INI_Close();

	new
		bufferArquivo[MAX_CHARS],

		linhasArquivo = 0xFFFFFFFF,

		bufferIntArquivo = 0xFFFFFFFF,

		File:arquivoFopen = fopen(arquivoLer, io_read);


	format(nomeArquivo, MAX_CHARS >>> 2, arquivoLer);

	while(fread(arquivoFopen, bufferArquivo))
	{

		bufferIntArquivo = strfind(bufferArquivo, "=", true);

		if(bufferIntArquivo == -1 || bufferIntArquivo > MAX_CHARS) continue;
		
		bufferArquivo[strlen(bufferArquivo) - 2]  = '\0';

		format(valorKey[++linhasArquivo], MAX_CHARS >>> 1, bufferArquivo[bufferIntArquivo+1]);

		bufferArquivo[bufferIntArquivo] = EOS;

		format(nomeKey[linhasArquivo], MAX_CHARS >>> 1, bufferArquivo);

		valorNumerico[linhasArquivo] = INI_HashString(bufferArquivo);


	}
	totalLinhas = linhasArquivo+1;

	return fclose(arquivoFopen), true;
}


////////////////////////////////////////////////////////////////////////////////

CallBack INI_HashString(buffer[]) 
{
	new totalContado = 0;
	for(new i = strlen(buffer); i != -1; i--)
	{
		totalContado += buffer[i];
	}
	return  totalContado;
}

////////////////////////////////////////////////////////////////////////////////

CallBack INI_Save()
{
	new
		i = 0,
		line[MAX_CHARS]
	;

	new File:arquivoFopen = fopen(nomeArquivo, io_write);

	for( ; i != totalLinhas ; ++i)
	{	
		
		format(line, MAX_CHARS, "%s=%s\r\n", nomeKey[i], valorKey[i]);
		fwrite(arquivoFopen, line);
	}
	return fclose(arquivoFopen);
}

////////////////////////////////////////////////////////////////////////////////

CallBack INI_Print()
{
	for(new i ; i != totalLinhas ; ++i)
	{
		printf("%s=%s",nomeKey[i],valorKey[i]);
	}
	return true;
}

////////////////////////////////////////////////////////////////////////////////

CallBack INI_Close()
{
	nomeArquivo[0] = EOS;
	
	for(new i; i != totalLinhas ; ++i)
	{
		nomeKey[i][0] = EOS;
		valorKey[i][0] = EOS;
		valorNumerico[i] = 0;
	}	
	return totalLinhas = 0, true;
}



////////////////////////////////////////////////////////////////////////////////

CallBack INI_WriteString(keySet[], valueSet[])
{
	
	new i, valorGetNumerico = INI_HashString(keySet);


	for( ;  i != totalLinhas ; ++i) if(valorGetNumerico == valorNumerico[i])
	{
		if(strcmp(nomeKey[i], keySet, false)) continue;

		return strcpy(valorKey[i], valueSet, MAX_CHARS);		
	}
	valorNumerico[i]=valorGetNumerico ;

	return strcpy(nomeKey[i], keySet, MAX_CHARS), strcpy(valorKey[i], valueSet, MAX_CHARS), totalLinhas++, true;
}
stock INI_Rename(file[],name[])
{
    new File:old;old=fopen(file,io_read);
    new File:newf;newf =fopen(name,io_write);
    new buffer[1];new i;
    for (i = flength(old); i > 0; i--)
    {
        fputchar(newf, fgetchar(old, buffer[0],false),false);
    }
    fclose(old);fclose(newf);
}

////////////////////////////////////////////////////////////////////////////////

CallBack INI_WriteInt(keySet[], valueSet)
{
	static destinoString[20];
	format(destinoString, sizeof(destinoString), "%i", valueSet);
	return INI_WriteString(keySet, destinoString);
}

////////////////////////////////////////////////////////////////////////////////

CallBack INI_WriteFloat(keySet[],Float:valueSet)
{
	static destinoString[20];
	format(destinoString, sizeof(destinoString), "%f", valueSet);
	
	return INI_WriteString(keySet, destinoString);
}