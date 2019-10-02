/*This software is under the BSD licence:
Copyright (c) 2007, Sebastien Riou

All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer. 
Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution. 
Neither the name of "nimp software" nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission. 
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.*/

#define BMP2C_VERSION 0002
#define BMP2C_MIN_INI_VERSION 0

#define NEW_LINE_THRESHOLD_IN_OUTPUT_SOURCE_FILE 80

#define CST_BIT_BASE 0x0fffffff

#include <iostream>
#include <sstream>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <cctype>
#include <locale>
using namespace std;

#include "bmp_ffi.h"
#include "archive.h"
#include "error_msg.h"
#include "math.h"
#include "string_ext.h"
#include "win32ext.h" //libcomdlg32.a must be included in the project (can be comdlg32.lib on some compilers)
#include "numconv_stringstream.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//                        Global variables (used only in this file)                           //
////////////////////////////////////////////////////////////////////////////////////////////////
//parameters from command line:
string input_full_file_name;
string src_output_file_name;
//parameters from ini file:
unsigned int min_version;
string x_decl, x_decl_postfix, y_decl, y_decl_postfix;
string array_decl;
unsigned int data_size;
string data_map;
string preview_map;
unsigned int generate_preview_bmp;
unsigned int pause;
string src_endl_param;
//other global variables:
vector<int> src2dest;
vector<int> preview_src2dest;
string src_endl;


/////////////////////////////////////////////////////////////////////////////////////////////////
//                            Functions (used only in this file)                               //
/////////////////////////////////////////////////////////////////////////////////////////////////

void read_ini_file(ifstream &argfile)
try
{
	string section;
	do
	{
		argfile>>section;
	}
	while(section!="[bmp2c]" && !argfile.eof());
	if(argfile.eof())
	{
		stringstream msg;
		msg<<"ini file:failed to find the [bmp2c] section"<<endl;
		throw  error_msg(msg.str());
	}
	
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	argfile>>min_version;
	if(argfile.bad()||argfile.fail())
	{
		stringstream msg;
		msg<<"ini file:failed to read version info."<<endl;
		throw  error_msg(msg.str());
	}
   if(min_version>BMP2C_VERSION)
	{
	   stringstream msg;
	   msg<<"executable version too old:"<<endl;
	   msg<<"The version of this executable is: v";
	   msg<<BMP2C_VERSION<<endl;
	   msg<<"The specified ini files requires at least v";
	   msg<<min_version<<endl;
	   msg<<"Please download a compatible executable or adapt your ini file";
	   throw error_msg(msg.str());
	}
	if(min_version<BMP2C_MIN_INI_VERSION)
	{
	   stringstream msg;
	   msg<<"ini file version too old:"<<endl;
	   msg<<"This executable is backward compatible with ini files version from v";
	   msg<<BMP2C_MIN_INI_VERSION<<endl;
	   msg<<"Please download a compatible executable or adapt your ini file";
	   throw error_msg(msg.str());
	}
	
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, x_decl );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, x_decl_postfix );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, y_decl );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, y_decl_postfix );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, array_decl );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	argfile>>data_size;	
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, data_map );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	getline( argfile, preview_map );
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	argfile>>generate_preview_bmp;
	argfile.ignore(numeric_limits<streamsize>::max(),'=');
	argfile>>pause;
	if(min_version>0)
	{
	   argfile.ignore(numeric_limits<streamsize>::max(),'=');
	   argfile>>src_endl_param;
	}
	if(argfile.bad()||argfile.fail())
	{
		stringstream msg;
		msg<<"ini file:failed to find or convert parameters."<<endl;
		throw  error_msg(msg.str());
	}
}
ERROR_MSG_CATCH("read_ini_file(ifstream &argfile)")

void prepare_parameters()
try
{
   if(data_size>32) throw error_msg("data_size must be <=32");

   string input_file_name=input_full_file_name;
   input_file_name=win32ext::remove_return_file_name(input_file_name);
   
   string input_file_name_id=input_file_name;
   stringext::replace_each_of(input_file_name_id, ".\\/:?-&~^|*%+=∞≤#\"'()`@$£µß!;,<>ÈË˘‡ÙÍ˚Ó‚", "_");
 
   stringext::replace(x_decl, "#bmp2c_input_full_file_name#", input_full_file_name);
   stringext::replace(x_decl, "#bmp2c_input_file_name#", input_file_name);
   stringext::replace(x_decl, "#bmp2c_input_file_name_id#", input_file_name_id); 

   stringext::replace(x_decl_postfix, "#bmp2c_input_full_file_name#", input_full_file_name);
   stringext::replace(x_decl_postfix, "#bmp2c_input_file_name#", input_file_name);
   stringext::replace(x_decl_postfix, "#bmp2c_input_file_name_id#", input_file_name_id); 

   stringext::replace(y_decl, "#bmp2c_input_full_file_name#", input_full_file_name);
   stringext::replace(y_decl, "#bmp2c_input_file_name#", input_file_name);
   stringext::replace(y_decl, "#bmp2c_input_file_name_id#", input_file_name_id); 

   stringext::replace(y_decl_postfix, "#bmp2c_input_full_file_name#", input_full_file_name);
   stringext::replace(y_decl_postfix, "#bmp2c_input_file_name#", input_file_name);
   stringext::replace(y_decl_postfix, "#bmp2c_input_file_name_id#", input_file_name_id); 
   
   stringext::replace(array_decl, "#bmp2c_input_full_file_name#", input_full_file_name);
   stringext::replace(array_decl, "#bmp2c_input_file_name#", input_file_name);
   stringext::replace(array_decl, "#bmp2c_input_file_name_id#", input_file_name_id);
   
   stringext::remove_white_spaces(data_map);
   stringext::remove_white_spaces(preview_map);
   
   if(src_endl_param=="CR_LF") src_endl="\r\n";
   if(src_endl_param=="LF") src_endl="\n";
   if(src_endl_param=="CR") src_endl="\r";
   if(src_endl.empty()) throw error_msg("src_endl_param must be one of the following vaues:\n"
                                        "'CR_LF'\n'LF'\n'CR'");
}
ERROR_MSG_CATCH("prepare_parameters()")

void compute_bit_manipulation()
try
{
   unsigned int i=0;
   while(i<data_map.length())
   {
      switch(data_map[i])
      {
         case 'c':
            i++;
            src2dest.push_back(data_map.at(i)-'0'+CST_BIT_BASE);
            break;
         case 'a':
            i++;
            src2dest.push_back(data_map.at(i)-'0'+24);
            break;
         case 'A':
            i++;
            src2dest.push_back(data_map.at(i)-'0'-24-1);
            break;
         case 'r':
            i++;
            src2dest.push_back(data_map.at(i)-'0'+16);
            break;
         case 'R':
            i++;
            src2dest.push_back(-data_map.at(i)+'0'-16-1);
            break;
         case 'g':
            i++;
            src2dest.push_back(data_map.at(i)-'0'+8);
            break;
         case 'G':
            i++;
            src2dest.push_back(-data_map.at(i)+'0'-8-1);
            break;
         case 'b':
            i++;
            src2dest.push_back(data_map.at(i)-'0');
            break;
         case 'B':
            i++;
            src2dest.push_back(-data_map.at(i)+'0'-1);
            break;
         default:
            throw error_msg(1,"unrecognized command in data_map");
      }
      i++;
   }
   if(src2dest.size()>data_size) throw error_msg(1,"data_map defines too much destination bits");
}
ERROR_MSG_CATCH("compute_bit_manipulation()")

void compute_preview_bit_manipulation()
try
{
   if(generate_preview_bmp)
	{
      unsigned int i=0;
      while(i<preview_map.length())
      {
         int factor=1;
         switch(preview_map[i])
         {
            case 'D':
               factor=-1;
            case 'd':
            {
               i++;
               numconv_stringstream conv;
               string::size_type pos=i;
               pos=preview_map.find_first_not_of("0123456789", pos);
               if(pos!=string::npos)
                  pos=pos-i;
               conv<<preview_map.substr(i, pos);
               if(pos!=string::npos)
                  i+=pos-1;
               else
                  i=preview_map.length();
               int val;
               conv>>val;
               if(factor<0)
                  val=-val-1;
               preview_src2dest.push_back(val);
               break;
            }
            case 'c':
               i++;
               preview_src2dest.push_back(preview_map.at(i)-'0'+CST_BIT_BASE);
               break;
            default:
               throw error_msg(1,"unrecognized command in preview_map");
         }
         i++;
      }
      if(preview_src2dest.size()>32) throw error_msg("preview_map defines more than 32 bits");
   }
}
ERROR_MSG_CATCH("compute_preview_bit_manipulation()")

//////////////////////////
// do_bit_manipulation  //
//////////////////////////
//
//perform bit manipulation on unsigned int value.
//the input value is transformed according to the operations stored in the bit_assignation vector
//each element of the vector describe the value of the corresponding bit 
//(the output value is always right justified)
//if the element is CST_BIT_BASE or CST_BIT_BASE+1, constant bit 0 or 1 respectively will be copied
//if the element is below CST_BIT_BASE, a bit from the input value will be copied
//    the value of the element indicates the index of the bit to copy
//
//example: 
//input value (in binary) = 01000001
//bit_assignation    = c1 c0  0  1   |  6  7 c0 c0 c1  (c1=CST_BIT_BASE+1 and c0=CST_BIT_BASE)              
//output (in binary) =  1  0  1  0   |  1  0  0  0  1
void do_bit_manipulation(unsigned int input, unsigned int &output, vector<int> bit_assignation)
try
{
   for(unsigned int bit_cnt=0;bit_cnt<bit_assignation.size();bit_cnt++)
   {
      unsigned int dest_bit=bit_assignation.size()-bit_cnt-1;
      bool bit;
      //compute bit value
      if(bit_assignation[bit_cnt]>=CST_BIT_BASE)//this bit is stuck to a constant value
      {
         if(bit_assignation[bit_cnt]>CST_BIT_BASE+1)
            throw error_msg("internal error: bit_assignation[bit_cnt]>CST_BIT_BASE+1");
         bit=bit_assignation[bit_cnt]-CST_BIT_BASE;
      }
      else
      {
         if(bit_assignation[bit_cnt]>=0)
            bit=(input>>bit_assignation[bit_cnt])&0x01;//get the pointed bit
         else
            bit=!((input>>(-bit_assignation[bit_cnt]-1))&0x01);//get the complement of the pointed bit
      }
      //modify output
      if(bit==0)
         output&=~(((unsigned int)bit)<<dest_bit);
      else
         output|=(((unsigned int)bit)<<dest_bit);
   }
}
ERROR_MSG_CATCH("do_bit_manipulation(unsigned int input, unsigned int &output, vector<int> bit_assignation)")

int main(int argc, char **argv)
try
{
   //check arguments and read ini file
   ifstream argfile;
	if(argc>=3 && argc <=4)
	{
		argfile.open(argv[1],ios::in);
		if(!argfile)
		{
			stringstream msg;
		   msg<<"can't open ini file '"<<argv[1]<<"'"<<endl;
		   throw  error_msg(msg.str());
		}
	}
	else
	{
		stringstream msg;
		msg<<"this program must be called with two or three arguments:"<<endl<<
			"the name of its ini file."<<endl<<
			"the name of the input bmp file with the extension."<<endl<<
			"the name of the output c file with the extension.(optional)"<<endl;
		throw  error_msg(msg.str());
	}

	input_full_file_name=argv[2];
	if(win32ext::is_directory(input_full_file_name))
	{
	   cout<<"input file is a directory: not yet implemented"<<endl;
	   return -1;
	}
	else
	{
	   cout<<"input file is a file"<<endl;
	}
	if(argc==4)
	{
		src_output_file_name=argv[3];
	}
	else
	{
		src_output_file_name=argv[2];
		src_output_file_name+="_out.c";
	}
   read_ini_file(argfile);
   argfile.close();
   
   prepare_parameters();
   
   compute_bit_manipulation();
   compute_preview_bit_manipulation();

	//open input bmp file
	archive fin(input_full_file_name.c_str(),ios::in);
	if(!fin)
	{
		stringstream msg;
		msg<<"can't create file '"<<input_full_file_name<<"'"<<endl;
		throw error_msg(msg.str());
	}

	//create an file format interface (ffi) for the bmp picture
	bmp_ffi bmp;
	cout<<"Read input file..."<<endl;
	fin>>bmp; //read from input file
	fin.close();//close it

	//create output bmp file
	ofstream fout(src_output_file_name.c_str(),ios::out|ios::binary);
	if(!fout)
	{
		stringstream msg;
		msg<<"can't create file '"<<src_output_file_name<<"'"<<endl;
		throw error_msg(msg.str());
	}
	
	cout<<"Write to output file..."<<endl;
	unsigned int x=bmp.get_x();
	unsigned int y=bmp.get_y();
	
	if(stringext::is_not_blank(x_decl))
	{
	   fout<<x_decl<<x<<x_decl_postfix<<src_endl;
	}

	if(stringext::is_not_blank(y_decl))
	{
	   fout<<y_decl<<y<<y_decl_postfix<<src_endl;
	}
	
	unsigned int line_char_cnt=array_decl.length()+4;	
	fout<<array_decl<<" {";
	
	bmp_ffi preview_bmp(x,y,24);
   
	for(unsigned int i=0;i<x;i++)
	{
		for(unsigned int j=0;j<y;j++)
		{
		   //limit line length in output source file 
         if(line_char_cnt>NEW_LINE_THRESHOLD_IN_OUTPUT_SOURCE_FILE)
			{
			   line_char_cnt=0;
			   fout<<src_endl;
			}
			
		   //read original pixel and store it into a 32 bit value as follow 0xaarrggbb
		   unsigned int input_dword=0;
		   input_dword|=((unsigned int)(bmp(i,j).alpha))<<24;
			input_dword|=((unsigned int)(bmp(i,j).red))<<16;
			input_dword|=((unsigned int)(bmp(i,j).green))<<8;
			input_dword|=bmp(i,j).blue;

         //compute value to write in the output source file
         unsigned int output_dword=0;
         do_bit_manipulation(input_dword, output_dword, src2dest);
         //write it
			stringstream outstr;
			outstr<<"0x"<<hex<<setw(data_size/4)<<setfill('0')<<output_dword;
			if(i+1<x || j+1<y)
			   outstr<<", ";
         fout<<outstr.str();
			line_char_cnt+=outstr.str().length();
			
			if(generate_preview_bmp)
	      {
	         //compute pixel value for preview bitmap
	         unsigned int preview_dword=0;
	         do_bit_manipulation(output_dword, preview_dword, preview_src2dest);
   			//store it
   			preview_bmp(i,j).alpha=(preview_dword>>24) & 0xff;
   			preview_bmp(i,j).red=(preview_dword>>16) & 0xff;//red
   			preview_bmp(i,j).green=(preview_dword>>8) & 0xff;//green
   			preview_bmp(i,j).blue=preview_dword & 0xff;//blue
   		}
		}
	}
	//close output source file
	fout<<"};"<<src_endl<<src_endl;
	fout.close();

	string preview_bmp_file_name=src_output_file_name+"_preview.bmp";
	if(generate_preview_bmp)
	{
	   //write preview bitmap file
		archive fconv(preview_bmp_file_name.c_str(),ios::out);
		if(!fconv)
		{
			stringstream msg;
			msg<<"can't create file '"<<preview_bmp_file_name<<"'"<<endl;
			throw error_msg(msg.str());
		}
		fconv<<preview_bmp;
		fconv.close();
	}
	if(pause) {system("pause");}
   return 0;
}
catch(error_msg e)
{
   cout <<e.get_err_text()<<endl<<"Error code "<<e.get_err_code()<<endl;
   system("pause");
	return e.get_err_code();
}
catch(...)
{
   cout <<"unknown exception caught !"<<endl;
   system("pause");
	return -1;
}

