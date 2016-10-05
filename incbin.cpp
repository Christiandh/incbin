#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
    if(argc <= 2)
    {
        printf("Usage: %s variablename datafile\n", argv[0]);
        return -1;
    }

    char *DataFilename = argv[2];
    FILE *DataFile = fopen(DataFilename, "rb");
    if(DataFile)
    {
        fseek(DataFile, 0, SEEK_END);
        unsigned long long FileLength = ftell(DataFile);
        rewind(DataFile);

        unsigned char *Data = (unsigned char *)malloc(FileLength);
        if(Data)
        {
            size_t BytesRead = fread(Data, 1, FileLength, DataFile);
            if(BytesRead == FileLength)
            {
                const int ValuesPerLine = 16;
                const char *Indent = "\t";

                char *VariableName = argv[1];
                printf("unsigned char %s[%llu] = {", VariableName, FileLength);
                bool MultiLined = FileLength > ValuesPerLine;

                for(int DataIndex = 0; DataIndex < FileLength; ++DataIndex)
                {
                    if(MultiLined && (DataIndex % ValuesPerLine == 0))
                    {
                        printf("\n%s", Indent);
                    }

                    printf("0x%.2X", Data[DataIndex]);

                    if((DataIndex < FileLength - 1))
                    {
                        if((DataIndex + 1) % ValuesPerLine != 0)
                        {
                            printf(", ");
                        }
                        else
                        {
                            printf(",");
                        }
                    }
                }
                if(MultiLined)
                {
                    printf("\n");
                }
                printf("};\n");
            }
            else
            {
                printf("Error: Could only read %llu out of %llu bytes!\n", BytesRead, FileLength);
            }
        }
        else
        {
            printf("Error: Could not allocate %llu bytes of memory!\n", FileLength);
        }
    }
    else
    {
        printf("Error: Could not open file: %s\n", DataFilename);
    }

    return 0;
}
