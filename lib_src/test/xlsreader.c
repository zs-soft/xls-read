#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "xls.h"

typedef struct xls_data_t{
    int row;
    int col;
    void *pwb;
    unsigned char ***data;
}xls_data;

int get_xls_rows_and_cols(const char *file_name, int *row, int *col){
    xlsWorkBook* pWB;
    xlsWorkSheet* pWS;
    if(file_name == NULL){
        if(row){
            *row = -1;
        }
        if (col){
            *col = -1;
        }
        
        return 0;
    }
    
    pWB=xls_open(file_name, "UTF-8");
    if (pWB!=NULL)
    {
        pWS=xls_getWorkSheet(pWB,0);
        xls_parseWorkSheet(pWS);
        if(row){
            *row = pWS->rows.lastrow + 1;
        }
        if (col){
            *col = pWS->rows.lastcol;
        }
     
        xls_close_WS(pWS);
        xls_close(pWB);
    }else{
        if(row){
            *row = -1;
        }
        if (col){
            *col = -1;
        }
    }
    
    return 0;
}

xls_data read_xls(const char *file_name){
    xlsWorkBook* pWB;
    xlsWorkSheet* pWS;
    unsigned int i, j;
    int len;
    struct st_row_data* row;
    WORD t,tt;
    xls_data data;
    memset(&data, 0, sizeof(xls_data));
    
    if(file_name == NULL){
        data.row = -1;
        data.col = -1;
        return data;
    }
    
    pWB=xls_open(file_name, "UTF-8");
    if (pWB!=NULL)
    {

//        for (i=0;i<pWB->sheets.count;i++)
//            printf("Sheet N%i (%s) pos %i\n",i,pWB->sheets.sheet[i].name,pWB->sheets.sheet[i].filepos);
        
        pWS=xls_getWorkSheet(pWB,0);
        xls_parseWorkSheet(pWS);
        
        data.row = pWS->rows.lastrow + 1;
        data.col = pWS->rows.lastcol;
        
//        printf("%d %d\n", data.row, data.col);
        unsigned char ***q = (unsigned char ***)malloc(data.row);

        for(i = 0; i < data.row; i++){
            unsigned char **p = (unsigned char **)malloc(data.col);
            q[i] = p;
        }
        //printf("i: %d\n", i);
        data.data = q;

        unsigned char ***info = data.data;
        unsigned char *l_info[data.row][data.col];
        for(i = 0; i < data.row; i++){
            for(j = 0; j < data.col; j++){
                l_info[i][j] = NULL;
            }
        }
        for (t=0;t<=pWS->rows.lastrow;t++)
        {
            row=&pWS->rows.row[t];
            //        xls_showROW(row->row);
            for (tt=0;tt<pWS->rows.lastcol;tt++)
            {
                if (!row->cells.cell[tt].isHidden)
                {
                    if (row->cells.cell[tt].str!=NULL && row->cells.cell[tt].str[0]!='\0'){
                        //printf("t: %d tt: %d %s\n", t, tt, row->cells.cell[tt].str);
                        len = strlen((const char *)row->cells.cell[tt].str);
                        //printf("len: %d\n", len);
                        l_info[t][tt] = (unsigned char *)malloc(len + 1);
                        memset((char *)l_info[t][tt], 0, (len + 1));
                        memcpy((char *)l_info[t][tt], (char *)row->cells.cell[tt].str, len);
                        //strcpy((char *)info[t][tt], (char *)row->cells.cell[tt].str);
                        //info[t][tt] = row->cells.cell[tt].str;
                    }
                }
            }
        }
//        printf("Count of rows: %i\n",pWS->rows.lastrow);
//        printf("Max col: %i\n",pWS->rows.lastcol);
//        printf("Count of sheets: %i\n",pWB->sheets.count);
        
       // xls_showBookInfo(pWB);
        //printf("%s\n", info[2][0]);
        //xls_close_WS(pWS);
        

//        for(i = 0; i < data.row; i++){
//            printf("第%d行: \n", i + 1);
//            for(j=0; j < data.col;j++){
//                if(l_info[i][j]){
//                    printf("i: %d j: %d %s \n", i, j, l_info[i][j]);
//                }
//                else
//                    printf("%d_%d is NULL\n", i, j);
//            }
//            printf("\n");
//        }

        for(i = 0; i < data.row; i++){
            for(j = 0; j < data.col; j++){
                //printf("i: %d   j: %d  \n", i, j);
                info[i][j] = l_info[i][j];
            }
        }
        
        
    }
    
    if(pWB){
        data.pwb = pWB;
        //xls_close(pWB);
    }
    
    return data;
}

void release_xls_data(xls_data *data){
    if(data == NULL)
        return;
    
    int i, j = 0;
    for(i = 0; i < data->row; i++){
        printf("第%d行: \n", i + 1);
        for(j=0; j < data->col;j++){
            if(data->data[i][j]){
                printf("i: %d j: %d %s \n", i, j, data->data[i][j]);
                free(data->data[i][j]);
            }
            else
                printf("%d_%d is NULL\n", i, j);
        }
        printf("\n");
        free(data->data[i]);
    }
    free(data->data);
    
    xlsWorkBook* pWB = (xlsWorkBook*)data->pwb;
    xls_close(pWB);
}

int main(int argc, char **argv){
    //printf("%s\n", argv[1]);
    xls_data data = read_xls(argv[1]);
    release_xls_data(&data);
//    int l1, l2;
//    get_xls_rows_and_cols(argv[1], &l1, &l2);
    //printf("row: %d, col: %d\n", l1, l2);
    return 0;
}
