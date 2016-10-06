#include <stdio.h>
#include <stdlib.h>

#define VALUES_PER_LINE 16
#define LINE_INDENT "\t"

int main(int argc, char *argv[])
{
    if(argc < 3)
    {
        printf("Usage: %s variablename datafilename\n", argv[0]);
        return -1;
    }

    int Result = 0;
    char *DataFilename = argv[2];
    FILE *DataFile = fopen(DataFilename, "rb");
    if(DataFile)
    {
        fseek(DataFile, 0, SEEK_END);
        size_t FileLength = ftell(DataFile);
        rewind(DataFile);

        unsigned char *Data = (unsigned char *)malloc(FileLength);
        if(Data)
        {
            size_t BytesRead = fread(Data, 1, FileLength, DataFile);
            if(BytesRead == FileLength)
            {
                char *VariableName = argv[1];
                printf("unsigned char %s[%zu] = {", VariableName, FileLength);
                int MultiLined = FileLength > VALUES_PER_LINE;

                for(int DataIndex = 0; DataIndex < FileLength; ++DataIndex)
                {
                    if(MultiLined && (DataIndex % VALUES_PER_LINE == 0))
                    {
                        printf("\n%s", LINE_INDENT);
                    }

                    printf("0x%.2X", Data[DataIndex]);

                    if((DataIndex < FileLength - 1))
                    {
                        if((DataIndex + 1) % VALUES_PER_LINE != 0)
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
                fprintf(stderr, "Error: Read %zu out of %zu bytes!\n", BytesRead, FileLength);
                Result = -4;
            }
        }
        else
        {
            fprintf(stderr, "Error: Could not allocate %zu bytes of memory!\n", FileLength);
            Result = -3;
        }
    }
    else
    {
        fprintf(stderr, "Error: Could not open file: %s\n", DataFilename);
        Result = -2;
    }

    return Result;
}
