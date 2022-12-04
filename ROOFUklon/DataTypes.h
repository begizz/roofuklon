#pragma once

struct ou_unit
{
	int a;
	int b;
	int c;
	int d;
	int dobor;
};

struct ku_unit
{
	int ugol;
	int uklon;
	int dobor1;
	int dobor2;
};

struct ou_data
{
	AcDbObjectId oId;
	double width;
	int length;
};

struct ku_data
{
	AcDbObjectId oId;
	int length;
	int cnt;
	int tip;
};

struct table_data
{
	CString a[3];
	CString b[3];
	CString c[3];
	CString d[3];
	CString dobor[3];

	CString ugol600[3];
	CString uklon600[3];
	CString dobor1600[3];
	CString dobor2600[3];

	CString ugol300[3];
	CString uklon300[3];
	CString dobor1300[3];
	CString dobor2300[3];

	CString ugol200[3];
	CString uklon200[3];
	CString dobor1200[3];
	CString dobor2200[3];
};