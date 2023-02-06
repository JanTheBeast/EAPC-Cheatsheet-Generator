// Inspired by:
// "https://github.com/Erfaniaa/codes2pdf"
// "https://github.com/pin3da/notebook-generator"

#include <windows.h>
#include <shlwapi.h>
#include <stdio.h>

#define MAX_FILE_SIZE 100'000
#define VERBOSE

char* str_replace(const char* string, size_t size, const char* substr, const char* replacement)
{
    char* buffer = (char*) calloc(size, sizeof(char));
    char* p;
    if(!(p = strstr(string, substr))) 
    {
        strcpy(buffer, string);
        return buffer;
    }
    
    strncpy(buffer, string, p - string);
    buffer[p - string] = '\0';

    sprintf(buffer + (p - string), "%s%s", replacement, p + strlen(substr));

#ifdef VERBOSE
    printf("Replaced first occurence of %s with %s.\n", substr, replacement);
#endif

    return buffer;
}

char* remove_extension(const char* string)
{
    char* retString = (char*) malloc(strlen(string) + 1);
    if(string == NULL) return NULL;
    strcpy(retString, string);
    char* lastExt = strrchr(retString, '.');
    char* lastPath = strrchr(retString, '\\');

    if (lastExt != NULL) {
        if (lastPath != NULL) 
        {
            if (lastPath < lastExt) *lastExt = '\0';
        } else *lastExt = '\0';
    }

    return retString;
}

void read_file(char* buffer, const char* fileName)
{
    HANDLE handleRead;
    DWORD bytesRead = 0;

    handleRead = CreateFile(
        fileName,
        GENERIC_READ,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(handleRead == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile failed (%ld)\n", GetLastError());
        return;
    }

    if(ReadFile(handleRead, buffer, MAX_FILE_SIZE - 2, &bytesRead, NULL) == FALSE)
    {
        printf("ReadFile failed (%ld)\n", GetLastError());
        CloseHandle(handleRead);
        return;
    }

    CloseHandle(handleRead);

    if(bytesRead <= 0 || bytesRead >= MAX_FILE_SIZE)
    {
        printf("Something went wrong reading from %s.\n", fileName);
    }

#ifdef VERBOSE
    printf("Read %ld bytes from %s.\n", bytesRead, fileName);
#endif
}

void write_file(char* buffer, const char* fileName)
{
    HANDLE handleWrite;
    DWORD bytesWritten;

    handleWrite = CreateFile(
        fileName,
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_NEW,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if(GetLastError() == ERROR_FILE_EXISTS)
    {
        printf("%s already exists, do you wish to overwrite? (Y/N) ", fileName);
        if(getchar() == 'Y')
        {
            handleWrite = CreateFile(
                fileName,
                GENERIC_WRITE,
                0,
                NULL,
                OPEN_EXISTING,
                FILE_ATTRIBUTE_NORMAL,
                NULL
            );
        }
    }

    if(handleWrite == INVALID_HANDLE_VALUE)
    {
        printf("CreateFile failed (%ld)\n", GetLastError());
        return;
    }

    char* nullByte = strchr(buffer, '\0');
    if(WriteFile(handleWrite, buffer, nullByte - buffer, &bytesWritten, NULL) == FALSE)
    {
        printf("WriteFile failed (%ld)\n", GetLastError());
        CloseHandle(handleWrite);
        return ;
    }

    CloseHandle(handleWrite);

    if(bytesWritten <= 0 || bytesWritten > MAX_FILE_SIZE)
    {
        printf("Something went wrong writing to %s.\n", fileName);
    }

#ifdef VERBOSE
    printf("Wrote %ld bytes to %s.\n", bytesWritten, fileName);
#endif
}

void add_section(char* buffer, const char* sectionName, int depth)
{
    char begin[256] = {0};
    strcat(begin, "\n\\");
    for(int i = 0; i < depth; i++) strcat(begin, "sub");
    strcat(begin, "section{");
    strcat(begin, sectionName);
    strcat(begin, "}\n");
    strcat(buffer, begin);
}

char* add_sections(const char* filePath, int depth)
{
    char* section = (char*) calloc(MAX_FILE_SIZE, sizeof(char));
    depth = depth < 3 ? depth : 3;

    char szFullPattern[MAX_PATH];
    WIN32_FIND_DATA FindFileData;
    HANDLE hFindFile;
    PathCombine(szFullPattern, filePath, "*");
    hFindFile = FindFirstFile(szFullPattern, &FindFileData);
    if(hFindFile != INVALID_HANDLE_VALUE)
    {
        do
        {
            if(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY
            && FindFileData.cFileName[0] != '.')
            {
                add_section(section, FindFileData.cFileName, depth);
                PathCombine(szFullPattern, filePath, FindFileData.cFileName);
                char* recursion = add_sections(szFullPattern, depth + 1);
                strcat(section, recursion);
                free(recursion);
            }
            else if(FindFileData.cFileName[0] != '.')
            {
                char* ext = PathFindExtension(FindFileData.cFileName);
                int isTex = *++ext == 't';
                isTex = isTex && *++ext == 'e';
                isTex = isTex && *++ext == 'x';
                char* extless = remove_extension(FindFileData.cFileName);
                add_section(section, extless, depth);
                free(extless);
                if(!isTex) strcat(section, "\\begin{lstlisting}\n");
                char* file = (char*) calloc(MAX_FILE_SIZE, sizeof(char));
                PathCombine(szFullPattern, filePath, FindFileData.cFileName);
                read_file(file, szFullPattern);
                strcat(section, file);
                strcat(section, "\n");
                free(file);
                if(!isTex) strcat(section, "\\end{lstlisting}\n");
            }
        } while (FindNextFile(hFindFile, &FindFileData));
        FindClose(hFindFile);
    }

    return section;
}

int main(int argc, char* argv[])
{ 
    if(argc < 4)
    {
        char path[MAX_PATH];
        GetModuleFileName(NULL, path, MAX_PATH);
        char* exe = PathFindFileName(path);

        printf(
            "Please enter the command in the format: %s [%s] [%s] [%s] [%s]",
            exe,
            "title",
            "team name",
            "code folder",
            "output file"
        );
        printf(
            "\nOr in the format: %s [%s] [%s] [%s]",
            exe,
            "title",
            "team name",
            "code folder"
        );
        printf("\n\nPress ENTER to close.");
        getchar();
        return -1;
    }

    char* buffer = (char*) calloc(MAX_FILE_SIZE, sizeof(char));
    read_file(buffer, "template.tex");

    char* temp = buffer;
    buffer = str_replace(buffer, MAX_FILE_SIZE, "$title$", argv[1]);
    free(temp);
    temp = buffer;
    buffer = str_replace(buffer, MAX_FILE_SIZE, "$author$", argv[2]);
    free(temp);

    char* sections = add_sections(argv[3], 0);
    strcat(buffer, sections);
    free(sections);
    
    strcat(buffer, "\\end{multicols}\n");
    strcat(buffer, "\\end{document}\n");

    if(argc == 5) write_file(buffer, argv[4]);
    else write_file(buffer, "cheatsheet.tex");

#ifdef VERBOSE
    printf("Press ENTER to close.");
    getchar();
#endif

    return 0;
}