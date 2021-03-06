#include "sftp.h"
#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

static char *_server = "u38989.ssh.masterhost.ru";
static char *_user = "u38989";
static char *_password = "amitin9sti";
static char *_dstDirectory = "/home/u38989";

static char *downloadError = "Can't dopwnload";
static char *uploadError = "Can't upload";

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	int status;
	int errorLog = -1;
	
	errorLog = open("error.log", O_CREAT);
	if( errorLog < 0 ) {
		exit(1);
	}
	
	status = sftpInit( _server, _user, _password );
	if( status != 0 ) {
		write( errorLog, "Can't init...\n", 12 );
		return 1;
	}

	status = sftpDownload("download.dat", "download.dat", _dstDirectory);
	if (status != 0) {
		write(errorLog, downloadError, strlen(downloadError));
	} 

	status = sftpUpload("upload.dat", "upload.dat", _dstDirectory, 1);
	if (status != 0) {
		write(errorLog, uploadError, strlen(uploadError));
	}

	sftpClose();

	close(errorLog);

	return 0;
}
