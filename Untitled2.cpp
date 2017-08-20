#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <locale>
#include <vector>

using namespace std;


typedef struct theloai {
	int maTheLoai;
	string tenTheLoai;
	int soLuongTruong;
	string *dsTruong;	
	theloai *next;
}TheLoai;


typedef struct tu {
	string ten;
	int maTL;
	string *thuocTinh;
	tu *next;
}Tu;

// khoi tao gia tri cua tong so thê loai, tong so tu, va cac danh sach moc noi
int tongSoTheLoai=0, tongSoTu=0;
TheLoai* dsTheLoai= NULL;
Tu* dsTu= NULL;

// luu thong tin cua tung ma the loai chua so luong la bao nhieu
map<int,int > mapSoLuong;


string* cat_chuoi(string line, int sl);
void themDSTu(Tu **head,string Ten, int maTL,int soLuong, string line);
bool xoaDSTu(Tu **head, string ten);
Tu *timNutTu(Tu *head, string ten);
TheLoai *timNutTheLoai(TheLoai *head, int maTL);
void themDSTL(TheLoai **head, int maTL, string tenTheLoai,int soLuong ,string line );
bool xoaDSTheLoai (TheLoai **head, string ten);
void laySoLuong() ;
void ghiFileSoLuong();
void them_theloai ();
void docFileTheLoai ();
void docFileDanhSachTu () ;
bool kiemTra(int maTL);
void themTu();
void suaTu ();

bool suaTheLoai(int lc);
void sua_the_loai() ;
void ghiFileDanhSachTu();
void ghiFileTheLoai() ;
void thongKe() ;
void huyDanhSachTu(Tu* head) ;
void huyDanhSachTheLoai(TheLoai* head);
void suaTu ();
void xoaTu() ;
void timKiemTu ();
bool xoaTheLoai(int lc);
void xoa_theloai();
void xemTheLoai(TheLoai *node);
void xemTu(Tu *node, int sl);



// cat chuoi dua vao theo ky tu ";"
string* cat_chuoi(string line, int sl) {
			istringstream iss(line);
			int i=0;
			string chuoi;
    		string *ds = new string[sl];
   			 while (getline(iss, chuoi, ';'))
    		{
    		   	ds[i]= chuoi;       
				i++;
    		} 
			return ds;   
}



// them vao dau danh sach tu
void themDSTu(Tu **head,string Ten, int maTL,int soLuong, string line) {
	Tu *NodeTu= new Tu;
	NodeTu->ten =Ten;
	NodeTu->maTL= maTL;
    NodeTu->thuocTinh = cat_chuoi(line,soLuong);
	NodeTu->next= *head;
	*head=NodeTu;
}


// xoa tu trong danh sach theo ten
bool xoaDSTu(Tu **head, string ten) {
	Tu *prevNode = NULL;
	Tu *currNode = *head;
	while(currNode && (ten.compare(currNode->ten) != 0)) {
		prevNode = currNode;
		currNode = currNode->next;
		}		
		if (currNode) {
			if (prevNode) {
				prevNode->next = currNode->next;
				free (currNode);
				return true;
			} else {
				*head = currNode->next;
				free (currNode);
				return true;
			}
		}
	return false;
	
}

// tim kiem 1 node trong danh sach tu theo ten
Tu *timNutTu(Tu *head, string ten) {
	Tu *node;
	node = head;
	while ( node && ((node->ten).compare(ten)!= 0 ) ) {
		node= node->next;
	}
	return node;
}
// tim kiem 1 node trong danh sach the loai theo ma the loai
TheLoai *timNutTheLoai(TheLoai *head, int maTL) {
	TheLoai *node;
	node = head;
	while ( node && (node->maTheLoai != maTL)) {
		node= node->next;
	}
	return node;
}

// them vao list the loai
void themDSTL(TheLoai **head, int maTL, string tenTheLoai,int soLuong ,string line ){
	TheLoai *NodeTL = new TheLoai; 
	NodeTL->maTheLoai= maTL;
	NodeTL->soLuongTruong = soLuong;
	NodeTL->tenTheLoai= tenTheLoai;
    NodeTL->dsTruong = cat_chuoi(line,soLuong);
	// them vao dau danh sach moc noi
	NodeTL->next= *head;
	*head = NodeTL;
}

bool xoaDSTheLoai (TheLoai **head, string ten) {
	TheLoai *prevNode = NULL;
	TheLoai *currNode = *head;
	while(currNode && (ten.compare(currNode->tenTheLoai) != 0)) {
		prevNode = currNode;
		currNode = currNode->next;
	}		
	if (currNode) {
		if (prevNode) {
			prevNode->next = currNode->next;
			free (currNode);
			return true;
		} else {
			*head = currNode->next;
			free (currNode);
			return true;
		}
	}
	return false;
	
}


// lay so luong cac truong cua tung the loai tu file soLuong.txt --> map< >: mapSoLuong
void laySoLuong() {
	fstream f;
	f.open("soluong.txt", ios::in);
 
	string duLieu;
	string chuoi, chuoi1;
	string kyTu = ":";
	int chiSo, giaTri;
 
	string line;
	while (!f.eof())
	{
		getline(f, line);
		chuoi = line.substr(0, line.find(kyTu)); // cat chuoi tu vi tri 0->vi tri chua ky tu
        chuoi1= line.substr(chuoi.length()+1, line.find('\n'));
       
		chiSo = atoi(chuoi.c_str());	// chuyen doi string->int
		giaTri = atoi(chuoi1.c_str());	
		mapSoLuong.insert(pair<int , int>(chiSo, giaTri));       // them vao map
	}	
	
	f.close();
}

// ghi so luong the loai vao file soLuong.txt tu map<>: mapSoLuong
void ghiFileSoLuong(){
	int dem=0;
	int chiSo, giaTri ;
	fstream ft;
	ft.open("soluong.txt",ios::out);

	map <int, int> :: iterator itr;
 	for (itr = mapSoLuong.begin(); itr != mapSoLuong.end(); ++itr)// duyet tu dau toi cuoi map
    {
       dem++;
       chiSo = itr->first ;
       giaTri = itr->second ;
      
 		if(dem == tongSoTheLoai) {   
       		ft<<chiSo<<":"<<giaTri; //neu la dong cuoi cung
       	}
       	else {
		   	ft<<chiSo<<":"<<giaTri<<endl;// neu chua phai la dong cuoi
		}     
    }	
	ft.close();
}


// them the loai 
void themTheLoai () {
	int n=0;
	int chiSo = 1 ;
	string ten;
	string duLieu="";
	string truong;
	map <int, int> :: iterator itr;	
 	for (itr = mapSoLuong.begin(); itr != mapSoLuong.end(); ++itr) // tim ma the loai chua ton tai 
    {
       if(chiSo == itr->first) {
	   		chiSo ++;
	   }
       
    }	
	
	
	cout<<"NHAP DU LIEU THE LOAI CAN THEM !"<<endl<<endl;
	cout<<"Nhap vao ten the loai :";
	getline(cin,ten);
	
	cout<<"Nhap vao so luong truong : ";
	cin>>n;
	fflush(stdin);
	
	// them vào danh sach so luong truong cua moi the loai
	mapSoLuong.insert(pair<int , int>(chiSo, n));	
	
	for( int i = 0 ; i < n ; i ++) {		
		cout<<"Nhap vao truong thu "<<i+1<<" : ";
		getline(cin,truong);
		fflush(stdin);
		duLieu+=truong+";";
	}
	
	// them vao list cac the loai
	themDSTL(&dsTheLoai,chiSo,ten,n,duLieu);
	tongSoTheLoai++;
}


// doc file the loai
void docFileTheLoai () {

	
	ifstream f; 
	f.open("theloai.txt",ios::in);
	int maTL;
	int dem = 0;
	int sl;
	int i=0;
	string tenTheLoai; 
	string line;
	
			
	while (!f.eof())
	{	dem ++;
		getline(f, line);
		
		if( dem%3 == 1 ) { // neu la dong thu nhat
			maTL = atoi(line.c_str());
			sl=mapSoLuong[maTL];
		}
		if( dem%3 == 2 ) { // neu la dong thu hai
			tenTheLoai= line;
		}
		if( dem%3 == 0 ) { // neu la dong thu 3
			// them vao ds moc noi
			tongSoTheLoai ++;
			themDSTL(&dsTheLoai,maTL,tenTheLoai,sl,line);
		}
	}
	 
	f.close();
	
}


// doc file tu

void docFileDanhSachTu () {

	
	ifstream f; 
	f.open("danhsachtu.txt",ios::in);
	int maTL;
	int dem = 0;
	// luu so luong truong 
	int sl;
	int i=0;
   	string ten;
	string *thuocTinh;
	string line;
	string duLieu;
		
	while (!f.eof())
	{
		dem ++;
		getline(f, line);
		if(dem == 1) { // neu la dong thu nhat
			ten= line;
			}
		else if(dem == 2) { // neu la dong thu hai
				maTL=atoi(line.c_str());			
				sl = mapSoLuong[maTL];	
			}
		else { //neu chua la dong cuoi
			duLieu+=line+";";
		}
		if(dem == sl +2) { // neu la dong cuoi
			tongSoTu++;
			themDSTu(&dsTu,ten,maTL,sl,duLieu); // them vao danh sach the loai
			dem = 0; 
			duLieu = "";
		}
	} 
	f.close();
}

// kiem tra ma the loai da ton tai chua
bool kiemTra(int maTL) {
	map <int, int> :: iterator itr;
 	for (itr = mapSoLuong.begin(); itr != mapSoLuong.end(); ++itr) // duyet trong map
    {
       if(maTL == itr->first) {
	   		return true;
	   }
       
    }
    return false;
}

void themTu(){
	
	int maTL,sl;	
	string ten;
	string line;
	string thuocTinh="";
	cout<<"Nhap vao tu them : ";
	getline(cin,ten);
	fflush(stdin);

	cout<<"Nhap vao ma the loai : " ;
	cin>>maTL;
	fflush(stdin);
	// kiem tra ma the loai da ton tai chua
	do{
		if(!kiemTra(maTL)) {
			cout<<"Nhap sai ma the loai, nhap lai ma  : ";
			cin>>maTL;
			fflush(stdin);
		}else break;
	}while(1);
		
	sl = mapSoLuong[maTL];
	
	TheLoai *node;
	node = timNutTheLoai(dsTheLoai,maTL); // tim node the loai
	cout<<"Nhap vao gia tri cac truong !" <<endl;
	for( int i = 0 ; i < sl; i ++) {					// them gia tri cac truong
		cout<<"Nhap vao gia tri truong " <<node->dsTruong[i]<<" : ";
		getline(cin,line);
		fflush(stdin);
		thuocTinh += line +";";		
	}

 	themDSTu(&dsTu,ten,maTL,node->soLuongTruong,thuocTinh);
 	tongSoTu ++;
 	
 	
}




void suaTu () {
	int sl,luaChon;
	string ten,line;
	TheLoai *node ;
	
	Tu *currNode = dsTu;
	
	cout<<"Nhap vao tu can sua : ";
	getline(cin,ten);
	fflush(stdin);
	
	currNode = timNutTu(dsTu,ten); // tim node tu trong ds tu
		
		if (currNode) { // neu node do ton tai
			sl = mapSoLuong[currNode->maTL]; // lay so luong
			
			node = timNutTheLoai(dsTheLoai,currNode->maTL); // tim node tu
			
			cout<<endl<<"1."<<node->tenTheLoai<<" : "<<currNode->ten<<endl<<"2.Ma the loai : "<<currNode->maTL<<endl;
			for( int i= 0 ; i< sl ; i++) {
				cout<<(i+3)<<"."<<node->dsTruong[i]<<" : "<<currNode->thuocTinh[i]<<endl;
			}
		
			cout<<endl<<"Nhâp vao truong  thu mây cân sua : "<<endl;			
			cin>>luaChon;
			fflush(stdin);
			
			// neu lua chon 1 -> thay ten tu
			if( luaChon == 1) {
				cout<<"Nhap ten moi : ";
				getline(cin,line);
				fflush(stdin);
				currNode->ten = line;
			}
			else if( luaChon == 2 ) { //thay doi ma the loai
				xoaDSTu(&dsTu,ten);
				int maTL;
				string thuocTinh="";
				TheLoai *newNode;
			
				cout<<"Nhap vao ma the loai : " ;
				cin>>maTL;
				fflush(stdin);
			
				do{ // kiem tra ma the loai da ton tai chua
					if(!kiemTra(maTL)) {
						cout<<"Ma the loai khong ton tai, nhap lai ma  : ";
						cin>>maTL;
					}else break;
				}while(1);
				
				sl = mapSoLuong[maTL]; // lay so luong cua ma the loai do
				newNode= timNutTheLoai(dsTheLoai,maTL); // tim node the loai
				
				cout<<"Nhap vao gia tri cac truong !" <<endl; // nhap vao gia tri cac truong khi thay doi ma the loai
				for( int i = 0 ; i < sl; i ++) {
					cout<<"Nhap vao gia tri truong " <<newNode->dsTruong[i]<<" : ";
					getline(cin,line);
					fflush(stdin);
					thuocTinh += line +";";		
				}
				
				themDSTu(&dsTu,ten,maTL,newNode->soLuongTruong,thuocTinh);	// them vao danh sach tu			
			}
			else {
			
				cout<<node->dsTruong[luaChon-3]<<" : ";
				getline(cin,line);
				fflush(stdin);
				currNode->thuocTinh[luaChon-3] = line;
			}			
		}
		else {
			cout<<"Tu khong ton tai !"<<endl;
		}	
}


void xoaTu() {
	string ten;
	cout<<"Nhap vao tu can xoa : ";
	getline(cin,ten);
	fflush(stdin);
	
	if(xoaDSTu(&dsTu,ten)) {
		cout<<"Xoa thanh cong ! "<<endl;
		tongSoTu --;
	}else {
		cout<<"Tu khong ton tai !"<<endl;	
	}	
}



void timKiemTu () {
	int doDai, sl;
	string ten;
	string line;
	cout << "Nhap vao tu can tim kiem :" ;
	getline(cin,ten);
	fflush(stdin);
	
	doDai = ten.length();
	Tu *node=dsTu;
	TheLoai *nodeTL;

	 
	while ( node ) {// duyet toan danh sach
		line =(node->ten);
		line = line.substr(0,doDai);
		if( line.compare(ten) == 0 ) {
			sl = mapSoLuong[node->maTL];// lay so luong
			
			nodeTL = timNutTheLoai(dsTheLoai, node->maTL);	// tim node the loai	 
			
			cout<<node->ten<<endl<<"Ma the loai : "<<node->maTL<<endl;
			for ( int i =0 ; i <sl ; i ++) {
				cout<<nodeTL->dsTruong[i]<<" : "<<node->thuocTinh[i]<<endl;
			}
			
			cout<<endl<<endl;
			
		}
			node= node->next;
	}
}


bool xoaTheLoai(int lc) {
	int maTL;
	string ten;
	Tu *nodeTu;
	TheLoai *node;
	if(lc == 2) {
		cout << "Nhap vao ma the loai can xoa :" ;
		cin>>maTL;
		fflush(stdin);
		node = timNutTheLoai(dsTheLoai,maTL);
	}else if( lc ==1 ) {
			cout << "Nhap vao ten the loai can xoa :" ;
			getline(cin,ten);
			fflush(stdin);	
			node = dsTheLoai;	
			while(node && ((node->tenTheLoai).compare(ten) != 0)) {
				node = node->next;
			}
	}
	if(node) {         //neu node do ton tai
		xoaDSTheLoai(&dsTheLoai,node->tenTheLoai); // xoa node the loai
		nodeTu = dsTu;
		while ( nodeTu ) { // xoa node tu lien quan
			if (nodeTu->maTL == maTL) {
				xoaDSTu(&dsTu,nodeTu->ten);
				tongSoTu--;
			}
			nodeTu = nodeTu->next;
		}
		tongSoTheLoai --;
		mapSoLuong.erase(node->maTheLoai); // xoa khoi mapr
		return true;
	}else {
		return false;
	}
}

void xoa_theloai(){
	int  lc;
	do {
	cout << "Ban muon xoa theo : "<<endl<<"1. Theo ten " <<endl<<"2. Theo ma the loai "<<endl;
	cin>>lc;
	fflush(stdin);
	if( lc >2 || lc < 1) {
		cout<<"Nhap sai yeu cau nhap lai !"<<endl;
	}
	
	}while(lc >2 || lc < 1);
	
		if(xoaTheLoai(lc)) {
			cout<<"Xoa thanh cong !"<<endl;
		}
		else 
			cout<<"Ten the loai khong ton tai !"<<endl;
}

// in ra man hinh cac truong trong 1 the loai
void xemTheLoai(TheLoai *node) {
	cout<<"1.Ma the loai : "<<node->maTheLoai<<endl<<"2.Ten the loai : "<<node->tenTheLoai<<endl;
	for( int i=0; i < node->soLuongTruong;i ++) {
		cout<<(i+3)<<"."<<node->dsTruong[i]<<endl;
	}
		cout<<endl<<endl;
}

// in ra cac truong trong 1 tu
void xemTu(Tu *node, int sl) {
	cout<<"1.Ten : "<<node->ten<<endl<<"2.Ma the loai : "<<node->maTL<<endl;
	for( int i=0; i < sl;i ++) {
		cout<<(i+3)<<"."<<node->thuocTinh[i]<<endl;
	}
	cout<<endl<<endl;
}

// sua the loai
bool suaTheLoai(int lc) {
	int ma,maTL,luaChon,n,m,sl,dem=0;
	string truong,thuocTinh, ten, duLieu="",duLieuTu="";
	TheLoai *node;
	Tu *nodeTu=dsTu;
	if(lc == 2) {
		cout << "Nhap vao ma the loai can sua :" ;
		cin>>ma;
		fflush(stdin);
		node = timNutTheLoai(dsTheLoai,ma);                  
	}
	else if (lc == 1) {
		cout << "Nhap vao ten the loai can sua :" ;
		getline(cin,ten);
		fflush(stdin);
		node = dsTheLoai;
	
		while(node && ((node->tenTheLoai).compare(ten) != 0)) {
			node = node->next;
		}
	}
	if(node) {
		sl = node->soLuongTruong;
		
		cout<<"1.Ma the loai : "<<node->maTheLoai<<endl<<"2.Ten the loai : "<<node->tenTheLoai<<endl;
		for( int i=0; i < sl;i ++) {
			cout<<(i+3)<<"."<<node->dsTruong[i]<<endl;
		}
		cout<<sl+3<<".Them truong"<<endl<<sl+4<<".Xoa truong"<<endl;
		
		cout<<"Nhap vao truong thu may can sua :" ;
		cin>>luaChon;
		fflush(stdin);		
		// sua ma the loai
		if( luaChon == 1) {
		 do {
			cout<<"Nhap vao ma the loai moi: ";
			cin>>maTL;
			fflush(stdin);
			if(kiemTra(maTL)) {
				cout<<"Ma da trung. Moi nhap lai !"<<endl;
			}else {
				node->maTheLoai=maTL;	
				// sua tat ca cac tu co ma the loai lien quan					
				while(nodeTu ) {
					if(nodeTu->maTL == maTL) {
						nodeTu->maTL= maTL;			
					}
					nodeTu= nodeTu->next;
				}
				break;
			   }
			}while(1);
		}
		
		// sua ten the loai
		else if( luaChon == 2) {
			cout<<"Nhap vao ten the loai moi : ";
			getline(cin,ten);
			fflush(stdin);
			node->tenTheLoai= ten;
			xemTheLoai(node);	
			
		}
		
		// thay the 1 truong trong the loai
		else if( luaChon >2 && luaChon < (sl+3)) {
			cout<<"Nhap vao ten truong thay the moi : ";
			getline(cin,ten);
			fflush(stdin);
			node->dsTruong[luaChon-3]= ten;
			xemTheLoai(node);
			// sua tat ca cac tu thuoc the loai lien quan
			while(nodeTu ) {
				if(nodeTu->maTL == node->maTheLoai) {
					cout<<nodeTu->ten<<endl<<"Nhap vao truong  "<<node->dsTruong[luaChon-3] <<" vua thay doi :";
					getline(cin,truong);
					fflush(stdin);
					nodeTu->thuocTinh[luaChon-3]=truong;						
					xemTu(nodeTu,sl);						
				}
				nodeTu= nodeTu->next;
			}			
		}
		
		// them truong cho the loai
		else if( luaChon == sl+3 ) {
			
			cout<<"Nhap so luong truong muon them : ";
			cin>>n;
			fflush(stdin);
			
			for( int i = 0 ; i < sl ; i ++) { //lay du lieu cua truong cu
				duLieu += node->dsTruong[i]+";";
			}
			for(int i=0; i < n; i ++) { // lay du lieu moi nhap vao
				cout<<"Nhap ten truong thu " <<i+1<<" can them : ";
				getline(cin,truong);
				fflush(stdin);		
				duLieu +=truong+";";		
			}
			
			mapSoLuong[node->maTheLoai]= sl+n;// them vao mapSoLuong	
			node->soLuongTruong +=n;       // thay doi so luong trong the loai	
			node->dsTruong=cat_chuoi(duLieu,sl+n); // thay doi cac truong trong the loai
					
			xemTheLoai(node);
			// sua tat ca cac tu thuoc the loai lien quan
			nodeTu = dsTu;
			while(nodeTu) {
				if(nodeTu->maTL == node->maTheLoai) {
					dem++;
					cout<<dem<<" : "<<nodeTu->ten<<endl;
					for(int i = 0;i < node->soLuongTruong -n ; i++) {// lay du lieu cu
						duLieuTu +=nodeTu->thuocTinh[i] +";";
					}
					for(int i=0;i<n;i++) { // them du lieu moi
						cout<<"Nhap vao truong "<<node->dsTruong[sl+i]<<" : ";
						getline(cin,thuocTinh);
						fflush(stdin);
						duLieuTu +=thuocTinh+";";
					}
					
					nodeTu->thuocTinh=cat_chuoi(duLieuTu,sl+n); // sua doi cac thuoc tinh
					xemTu(nodeTu,sl+n);
					duLieuTu="";
				}
				nodeTu= nodeTu->next;
			}
			
			
		}
		else if(luaChon == sl+4) { // xoa 1 so truong trong the loai 
		
			cout<<"Nhap so luong truong muon xoa : ";
			cin>>n;
			int ds[n];
			fflush(stdin);
			for( int i = 0 ; i < sl ; i ++) {
				cout<<i+1<<":"<<node->dsTruong[i]<<endl;
			}
			cout<<"Nhap ma so cac truong xoa :"<<endl;
			for(int i=0;i <n;i++) { // nhap cac truong muon xoa
				cout<<"Truong thu "<<i+1<<" : ";
				cin>>m;
				fflush(stdin);
				ds[i] = m;
				node->dsTruong[m-1] ="";
			}
			for(int i=0;i < sl; i++ ) { // lay ra cac truong chua bi xoa
				if((node->dsTruong[i]).compare("") != 0) {
					duLieu += node->dsTruong[i]+";";
				}
			}
			node->soLuongTruong= sl-n; // thay doi so luong truong the loai
			node->dsTruong= cat_chuoi(duLieu,sl-n);// thay doi truong
			xemTheLoai(node);
		
			nodeTu= dsTu;
			while(nodeTu) { // thay doi cac tu thuoc the loai lien quan
				if(nodeTu->maTL == node->maTheLoai) {
					for(int i=0; i< n;i ++) {
						nodeTu->thuocTinh[i] ="";
					}					
					for(int i=0;i <sl;i++) {
						if(nodeTu->thuocTinh[i].compare("") != 0 ) {
							duLieuTu +=nodeTu->thuocTinh[i]+";";
						}
					}					
					nodeTu->thuocTinh= cat_chuoi(duLieuTu,sl-n);
					xemTu(nodeTu,sl-n);
					duLieuTu="";
				}				
				nodeTu = nodeTu->next;
			}			
		}
		return true;
	}else {
		return false;
	}
}


void sua_the_loai() { // khoi tao goi toi chuc nang sua the loai
	int  lc;
	do {
		cout << "Ban muon sua theo : "<<endl<<"1. Theo ten " <<endl<<"2. Theo ma the loai "<<endl;
		cin>>lc;
		fflush(stdin);
		if( lc >2 || lc < 1) {
			cout<<"Nhap sai yeu cau nhap lai !"<<endl;
		}	
	}while(lc >2 || lc < 1);
	
	
	if(suaTheLoai(lc)) {
		cout<<"Sua thanh cong !"<<endl;
	}
	else 
		cout<<"The loai khong ton tai !"<<endl;
}


void huyDanhSachTheLoai(TheLoai* head) {
	TheLoai *currNode = head, *nextNode= NULL;
	while(currNode != NULL) {
	nextNode = currNode->next;
	free(currNode);
	currNode = nextNode;
	}
}

void huyDanhSachTu(Tu* head) {
	Tu *currNode = head, *nextNode= NULL;
	while(currNode != NULL) {
	nextNode = currNode->next;
	free(currNode);
	currNode = nextNode;
}

}

//thong ke so luong tu trong the loai
void thongKe() {
	int maTL, dem = 0;
	Tu *node = dsTu;
	
	cout<<"Nhap vao ma the loai can thong ke : ";
	cin>>maTL;
	fflush(stdin);
	cout<<"Cac tu thuoc the loai "<<maTL<<" : "<<endl;
	while(node) {
		if(node->maTL == maTL) {
			dem ++;
			cout<<dem<<". "<<node->ten<<endl;
		}
		node= node->next;
	}
	
	cout<<endl<<"So tu thuoc the loai "<<maTL<<" la : "<<dem<<endl;
}

// ghi vao file theloai
void ghiFileTheLoai() {
	int sl,dem =0;
	string duLieu;
	TheLoai *node= dsTheLoai;
	fstream f;
	f.open("theloai.txt",ios::out);
	
	while(node) {
		dem++;
		sl=mapSoLuong[node->maTheLoai];
		
		for( int i=0; i< sl;i ++) {
			duLieu +=node->dsTruong[i]+";";
		}
		if(dem == tongSoTheLoai) {
			f<<node->maTheLoai<<endl<<node->tenTheLoai<<endl<<duLieu;
		}
		else {
			f<<node->maTheLoai<<endl<<node->tenTheLoai<<endl<<duLieu<<endl;	
		}
		duLieu="";			
		node= node->next;
	}
	
	f.close();
	
}

// ghi vao dile danhsachtu
void ghiFileDanhSachTu() {
	int sl,dem=0;
	Tu *node= dsTu;
	fstream f;
	f.open("danhsachtu.txt",ios::out);
	
	while(node) {
		dem ++;
		sl=mapSoLuong[node->maTL];
		f<<node->ten<<endl<<node->maTL<<endl;
		for( int i=0; i<sl-1;i ++) {
			f<<node->thuocTinh[i]<<endl;
		}		
		
		if(dem == tongSoTu) {
			f<<node->thuocTinh[sl-1];
		}
		else 
			f<<node->thuocTinh[sl-1]<<endl;
		node= node->next;
	}
	
	f.close();
	
}

void xemDSTheLoai() {
	
	TheLoai *node = dsTheLoai;
	while(node) {
		cout<<node->maTheLoai<<"."<<node->tenTheLoai<<endl;
		
		node=node->next;
	}
}


void batDau() {
	
	string luaChon;
	bool selec=false;
	
	while(!selec) {
		int lc;
		cout<<"Menu :"<<endl;
		cout<<"1. Tim kiem tu :"<<endl;
		cout<<"2. Them tu :"<<endl;
		cout<<"3. Sua tu :"<<endl;
		cout<<"4. Xoa tu :"<<endl;
		cout<<"5. Them the loai :"<<endl;
		cout<<"6. Sua the loai :"<<endl;
		cout<<"7. Xoa the loai :"<<endl;
		cout<<"8. Thong ke theo ma the loai :"<<endl;
		cout<<"9. Xem danh sach the loai :"<<endl;
		
		
		do {
			cout<<"Nhap chuc nang ban muon : ";
			cin>>lc;
			fflush(stdin);
			if( lc < 1 || lc > 9) {
				cout<<"Nhap sai, yeu cau nhap lai !"<<endl;
			}
		}
		while (lc < 1  || lc > 9 );
		
			if(lc == 1) {
				timKiemTu ();
			}
			else if(lc == 2) {
				themTu();
			}
			else if(lc == 3) {
				suaTu();
			}
			else if(lc == 4) {
				xoaTu();
			}
			else if(lc == 5) {
				themTheLoai();
			}
			else if(lc == 6) {
				sua_the_loai();
			}
			else if(lc == 7) {
				xoa_theloai();
			}
			else if(lc == 8) {
				thongKe();
			}
			else if(lc == 9) {
				xemDSTheLoai();
			}
		
			cout<<"Ban co muon thuc hien them chuc nang nao khong ? (y/n) : ";
			getline(cin,luaChon);
			fflush(stdin);
			if(luaChon.compare("y") != 0 ) {
				selec = true;
			}	
		}
}


int main () {
	
	laySoLuong();
 	docFileTheLoai();
	docFileDanhSachTu();
	batDau();
	ghiFileSoLuong();
	ghiFileDanhSachTu();
	ghiFileTheLoai() ;
	huyDanhSachTheLoai(dsTheLoai);
	huyDanhSachTu(dsTu);	
	return 0;
}
