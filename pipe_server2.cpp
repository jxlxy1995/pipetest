#include <stdio.h>  
#include <windows.h>  

#define PIPE_NAME L"\\\\.\\Pipe\\test"  

HANDLE g_hPipe = INVALID_HANDLE_VALUE;  

int main()  
{  
	char buffer[1024];  
	DWORD WriteNum;  

	printf("test server.\n");  
	g_hPipe = CreateNamedPipe(PIPE_NAME, PIPE_ACCESS_DUPLEX, PIPE_TYPE_BYTE|PIPE_READMODE_BYTE , 1, 0, 0, 1000, NULL);  
	if(INVALID_HANDLE_VALUE == g_hPipe)  
	{  
		printf("Create name pipe failed!\n");  
		printf("Close pipe.\n");  
		CloseHandle(g_hPipe);  
		system("pause");  
		return 0;  
	}  

	printf("Wait for connect...\n"); 
	if( false == ConnectNamedPipe(g_hPipe, NULL) )  
	{  
		printf("Connect failed!\n"); 
		printf("Close pipe.\n");  
		CloseHandle(g_hPipe); 
		system("pause");  
		return 0;  
	}  
	printf("Connected.\n");  

	while(1)  
	{  
		scanf("%s",buffer);  
		if(WriteFile(g_hPipe, buffer, /*(DWORD)*/strlen(buffer), &WriteNum, NULL) == FALSE)  
		{  
			printf("Write failed!\n");  
			break;  
		}  
	}

	printf("Close pipe.\n");
	DisconnectNamedPipe(g_hPipe);
	CloseHandle(g_hPipe);
	system("pause");  
	return 0;
}  