#include <stdexcept>
#include <xls.h>
#include <iostream>
using namespace xls;
using namespace std; 
///////////////////////////////////////////////// 
int main(int argc, char **argv) 
{ 
　　if (argc < 2) 
　　{ 
　　　　cerr << "please input the excel file." << endl;
　　　　return 1; 
　　} 

　　xlsWorkBook* pWorkBook = xls_open(argv[1], "UTF-8"); 
　　if (NULL == pWorkBook) 
　　{ 
　　　　cerr << "file is not excel" << endl;
　　　　return 1; 
　　}

　　xlsWorkSheet* pWorkSheet = xls_getWorkSheet(pWorkBook, 0); 
　　xls_parseWorkSheet(pWorkSheet);

　　for (int r=0; r<=pWorkSheet->rows.lastrow; r++) 
　　{
　　　　xlsRow* row = &pWorkSheet->rows.row[r]; 
　　　　for (int c=0; c<pWorkSheet->rows.lastcol; c++)
　　　　{
　　　　　　BYTE* pCurCellInfo = row->cells.cell[c].str;
　　　　　　if (NULL != pCurCellInfo)
　　　　　　{
　　　　　　　　cout << pCurCellInfo;
　　　　　　　　getchar(); 
　　　　　　}
　　　　} 
　　　　cout << endl;
　　}

　　xls_close_WS(pWorkSheet); 
　　xls_close_WB(pWorkBook); 

　　return 0; 
}
