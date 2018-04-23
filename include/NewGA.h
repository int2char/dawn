/*
 * this is a header and implement of serial GA
 * no correlate .cpp file exit;
 * */
#include"Graph.h"
#include "service.h"
#include"taskPath.h"
#include"valuemark.h"
#include"curand_kernel.h"
#include"iostream"
#include <fstream>
#include"const.h"
#include<algorithm>
#include<vector>
#include<math.h>
#include"BFS.h"
#include"time.h"
#include"PathArrange.h"
#include"float.h"
#include<map>
using namespace std;
#define power .5
#define NNN 10000
double distan[NNN];
int pedge[NNN];
struct FitVM {
	double value;
	int mark;
	FitVM(double _value=0,double _mark=0){
		value = _value;
		mark = _mark;
	}
};
class NewGA
{
	private:
	taskPath* PathSets;
	Graph &G;
	int*st;
	int*te;
	double*demand;
	int**chormes;
	int**childs;
	int**monsters;
	double*capacity;
	double best;
	int totalweight;
	vector<FitVM> Fits;
	vector<pair<int,vector<int>>> Result;
	vector<pair<double,int>>answers;
	public:
		NewGA( Graph &_G):G(_G){
			st = (int*)malloc(Task*sizeof(int));
			te = (int*)malloc(Task*sizeof(int));
			demand = (double*)malloc(Task*sizeof(double));
			capacity = (double*)malloc(sizeof(double)*EDge);
			for (int i = 0; i < EDge; i++)
				capacity[i] = G.incL[i].capacity;
			chormes = (int**)malloc(sizeof(int*)*pop);
			childs = (int**)malloc(sizeof(int*)*Beta);
			monsters = (int**)malloc(sizeof(int*)*Gama);
			for (int i = 0; i < pop; i++)
				chormes[i] = (int*)malloc(sizeof(int)*Task);
			for (int i = 0; i < Beta; i++)
				childs[i] = (int*)malloc(sizeof(int)*Task);
			for (int i = 0; i<Gama; i++)
				monsters[i] = (int*)malloc(sizeof(int)*Task);
		};
		~NewGA(){
			free(st);
			free(te);
			free(demand);
			free(capacity);
			free(chormes);
			free(childs);
			free(monsters);
		}
	public:

		//vector<int>
		vector<int> GAsearch(vector<service>&ser, taskPath*_PathSets){
			cout<<"ops"<<endl;
			vector<double>capacity(EDge,100);
			vector<pair<string,double>> rdata;
			vector<double>u(EDge,0.1);
			vector<vector<vector<double>>>spu(ser.size(),std::vector<std::vector<double>>());
			vector<double>f(EDge,0);
			vector<int>ids(ser.size(),0);
			vector<int>bids(ser.size(),0);
			vector<vector<pair<int,int>>>epath(EDge,vector<pair<int,int>>());
			map<pair<int,int>,vector<int>>pathe;
			vector<vector<double>>x(ser.size(),vector<double>());
			vector<vector<double>>cc(ser.size(),vector<double>());
			vector<double>y(ser.size(),0);
			vector<vector<double>>spy(ser.size(),vector<double>());
			vector<vector<double>>overtime(ser.size(),std::vector<double>());
			map<pair<int,int>,double>wsigu;
			map<pair<int,pair<int,int>>,double>overo;
			vector<double> tsum(ser.size(),-1e10);
			double alpha=6;
			double q=1.0;//0.98;
			std::vector<double>keep(ser.size(),1000);
			cout<<"asd"<<endl;
			cout<<"service size is "<<ser.size()<<endl;
			for(int i=0;i<ser.size();i++)
			{
				double as=0;
				int num=min(_PathSets[i].num,4);
				int j=0;
				if(_PathSets[i].Pathset[j][0]>-1)
					{
						std::vector<double> v;
						x[i].push_back(0);
						spy[i].push_back(100);
						spu[i].push_back(v);
						for(int M=0;M<EDge;M++)
							spu[i][spu[i].size()-1].push_back(0.1);
						as+=100;
					}
				int k=0;
				while(_PathSets[i].Pathset[j][k]>-1)
					{
						epath[_PathSets[i].Pathset[j][k]].push_back(make_pair(i,0));
						pathe[make_pair(i,0)].push_back(_PathSets[i].Pathset[j][k]);
						k++;
					}
					cc[i].push_back(0);
					overtime[i].push_back(1);
				for(int jj=1;jj<num;jj++)
					{
						int j=jj;//rand()%num;//(num-1)+1;
						if(_PathSets[i].Pathset[j][0]>-1)
							{
								std::vector<double> v;
								x[i].push_back(0);
								spy[i].push_back(100);
								spu[i].push_back(v);
								for(int M=0;M<EDge;M++)
									spu[i][spu[i].size()-1].push_back(0.1);
								as+=100;
							}
						int k=0;
						while(_PathSets[i].Pathset[j][k]>-1)
							{
								epath[_PathSets[i].Pathset[j][k]].push_back(make_pair(i,jj));
								pathe[make_pair(i,jj)].push_back(_PathSets[i].Pathset[j][k]);
								k++;
							}
							cc[i].push_back(0);
							overtime[i].push_back(1);
					}
				y[i]=100;
			}

			for(int i=0;i<ser.size();i++)
				for(int j=0;j<x[i].size();j++)
					if(pathe[make_pair(i,j)].size()<=0)
						cout<<"fucker"<<endl;
			double bestv=-INT_MAX/2;
			int count=0;
			double tt=1;
			double beta=0.05;
			double gama=0.05;
			int counter=0;
			time_t begin=clock();
			for(int t=0;t<100000;t++)
			{
				vector<double> sigxt(ser.size(),0);
				map<pair<int,int>,double>sigu;
				vector<double>esigxt(EDge,0);
				vector<double>asigxt(ser.size(),0);
				double objective=0;
				for(int i=0;i<ser.size();i++)
					for(int j=0;j<x[i].size();j++)
						for(int k=0;k<pathe[make_pair(i,j)].size();k++)
							esigxt[pathe[make_pair(i,j)][k]]+=x[i][j];
				for(int i=0;i<EDge;i++)
					{
							if(esigxt[i]-capacity[i]>1)
								{
									counter++;
									if(counter>100000&&beta>0){
										beta=0;
										gama/=5;
										cout<<"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
									}
									u[i]=u[i]+gama*u[i]*(esigxt[i]-capacity[i])/capacity[i];
							}	
							else
								u[i]=u[i]+beta*u[i]*(esigxt[i]-capacity[i])/capacity[i];
					}
				for(int i=0;i<EDge;i++)
					{
						for(int j=0;j<epath[i].size();j++)
							sigu[epath[i][j]]+=u[i];

					}
				for(int i=0;i<ser.size();i++)
				{
					for(int j=0;j<x[i].size();j++)
						asigxt[i]+=x[i][j];
					y[i]=y[i]+(0.05/12)*(asigxt[i]-y[i]);
				}
				for(int i=0;i<ser.size();i++)
					{
						double min=DBL_MAX;
						int id=-1;
						double toto=0;
						double sum=0;
						for(int j=0;j<x[i].size();j++)
						{
							double data=sigu[make_pair(i,j)];
							if(data<min){
								min=data;
								id=j;
							}
						}
						for(int j=0;j<x[i].size();j++)
							x[i][j]=0;
						x[i][id]=pow(pow(y[i],-alpha)/sigu[make_pair(i,id)],10)*y[i];
						ids[i]=id;
					}
				int overflow=0;
				for(int i=0;i<ser.size();i++)
					objective+=-pow(asigxt[i],-5)/5;
				if(objective>bestv&&overflow<100)
				{
					bestv=objective;
					bids=ids;
				}
				cout<<"obj is: "<<" "<<" "<<objective<<" "<<counter<<endl;
			}
			time_t end=clock();
			cout<<"time is "<<end-begin<<endl;
			/*int toto=0;

			for(int i=0;i<ser.size();i++)
				{	
					cout<<endl;
					for(int j=0;j<x[i].size();j++)
						cout<<cc[i][j]/15000<<" ";
				}
			cout<<">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl;
			//for(int i=0;i<ser.size();i++)
			//	cout<<ids[i]<<endl;
			cout<<"bestv is "<<bestv<<endl;
			cout<<"toto is "<<toto<<endl;*/
			return bids;
		};
	};

	/*void GAsearch(vector<service>&ser, taskPath*_PathSets)
			{
				_PathSets[111]=_PathSets[0];
				vector<int>ids(ser.size(),0);
				for(int k=0;k<100;k++)
				{
					for(int i=0;i<ser.size();i++)
						ids[i]=rand()%10;
					GAsearch(ser,_PathSets,ids);
				}
				
			}*/
		/*vector<pair<string,double> > GAsearch(vector<service>&ser, taskPath*_PathSets,std::vector<int> &ids){
			cout<<"ops"<<endl;
			vector<double>capacity(EDge,100);
			vector<pair<string,double>> rdata;
			vector<double>u(EDge,0.1);
			vector<vector<vector<double>>>spu(ser.size(),std::vector<std::vector<double>>());
			vector<double>f(EDge,0);
			vector<int>bids(ser.size(),0);
			vector<vector<pair<int,int>>>epath(EDge,vector<pair<int,int>>());
			map<pair<int,int>,vector<int>>pathe;
			vector<vector<double>>x(ser.size(),vector<double>());
			vector<double>y(ser.size(),0);
			vector<vector<double>>spy(ser.size(),vector<double>());
			vector<vector<double>>overtime(ser.size(),std::vector<double>());
			map<pair<int,int>,double>wsigu;
			vector<double> tsum(ser.size(),-1e10);
			double alpha=4;
			double q=0.9;
			std::vector<double>keep(ser.size(),1000);
			//cout<<"asd"<<endl;
			_PathSets[111]=_PathSets[0];
			for(int i=0;i<ser.size();i++)
			{
				double as=0;
				int num=min(_PathSets[i].num,1);
				//cout<<_PathSets[i].num<<endl;
				//for(int j=0;j<num;j++)
				{
					int j=ids[i];
					if(_PathSets[i].Pathset[j][0]>-1)
						{
							std::vector<double> v;
							x[i].push_back(100);
							spy[i].push_back(100);
							spu[i].push_back(v);
							for(int M=0;M<EDge;M++)
								spu[i][spu[i].size()-1].push_back(0.1);
							as+=100;
						}
					int k=0;
					while(_PathSets[i].Pathset[j][k]>-1)
						{
							epath[_PathSets[i].Pathset[j][k]].push_back(make_pair(i,0));
							pathe[make_pair(i,0)].push_back(_PathSets[i].Pathset[j][k]);
							k++;
						}
						//cout<<k<<endl;
						overtime[i].push_back(1);
				}
				y[i]=100;
			}

			for(int i=0;i<ser.size();i++)
				for(int j=0;j<x[i].size();j++)
					if(pathe[make_pair(i,j)].size()<=0)
						cout<<"fucker"<<endl;
			double bestv=-INT_MAX/2;
			int count=0;
			double tt=1;
			for(int t=0;t<5000;t++)
			{

				vector<vector<vector<double>>>tspu(ser.size(),std::vector<std::vector<double>>());
				vector<vector<double>>tspy(ser.size(),vector<double>());
				tspu=spu;
				tspy=spy;
				vector<double> sigxt(ser.size(),0);
				map<pair<int,int>,double>sigu;
				map<pair<int,int>,double>sigf;
				vector<double>esigxt(EDge,0);
				vector<double>tu(EDge,1);
				vector<double>asigxt(ser.size(),0);
				vector<double>ty(ser.size(),0);
				vector<vector<double>>tx(ser.size(),vector<double>());
				vector<double>flag(ser.size(),0);
				//cout<<"init sucess"<<endl;
				double objective=0;

				for(int i=0;i<ser.size();i++)
					for(int j=0;j<x[i].size();j++)
						for(int k=0;k<pathe[make_pair(i,j)].size();k++)
							esigxt[pathe[make_pair(i,j)][k]]+=x[i][j];
				for(int i=0;i<EDge;i++)
					{
							tu[i]=u[i]+(0.05)*u[i]*(esigxt[i]-capacity[i])/capacity[i];
					}
				for(int i=0;i<EDge;i++)
					for(int j=0;j<epath[i].size();j++)
						sigu[epath[i][j]]+=tu[i];
				for(int i=0;i<ser.size();i++)
				{
					for(int j=0;j<x[i].size();j++)
						asigxt[i]+=pow(x[i][j],q);
					ty[i]=y[i]+((1-q)/(2*(alpha+q-1)))*y[i]*(asigxt[i]-pow(y[i],q))/pow((y[i]),q);
				}
				for(int i=0;i<ser.size();i++)
					{
						double min=DBL_MAX;
						int id=-1;
						double toto=0;
						double sum=0;
						for(int j=0;j<x[i].size();j++)
						{
							double data=sigu[make_pair(i,j)];
							sum+=sigu[make_pair(i,j)];
							if(data<min){
								min=data;
								id=j;
							}
							toto+=data;
							tx[i].push_back(data);
						}
						for(int j=0;j<tx[i].size();j++)
							tx[i][j]=0;
						tx[i][id]=pow(pow(ty[i],-alpha)/sum,1/(1-q))*ty[i];
						ids[i]=id;
						flag[i]=0;
					}
				int overflow=0;
				vector<double> ca=capacity;
				double toto=0;
				for(int i=0;i<ser.size();i++)
				{
					for(int j=0;j<x[i].size();j++)
						{
							if(x[i][j]>0)
							toto+=x[i][j];
							for(int k=0;k<pathe[make_pair(i,j)].size();k++)
								ca[pathe[make_pair(i,j)][k]]-=x[i][j];
						}
				}
				int gg=0;
				for(int i=0;i<EDge;i++)
					if(ca[i]<-1)
						{
							gg=1;
							//cout<<"&&&&&&&&&&&&&&&&& "<<i<<endl;
							for(int k=0;k<epath[i].size();k++)
								{
									int a=epath[i][k].first;
									int b=epath[i][k].second;
									//if(x[a][b]>0)
										//cout<<"************ "<<a<<" "<<y[a]<<" "<<ty[a]<<" "<<x[a][b]<<" "<<wsigu[epath[i][k]]<<" "<<sigu[epath[i][k]]<<" "<<tx[a][b]<<endl;
								}
							overflow++;
						}
				x=tx;
				y=ty;
				spu=tspu;
				u=tu;
				spy=tspy;
				wsigu=sigu;
				for(int i=0;i<ser.size();i++)
					objective+=-pow(asigxt[i],-3)/3;
				//count++;
				//if(gg>0)cout<<t<<endl;
				if(objective>bestv&&overflow<100)
				{
					//count=0;
					bestv=objective;
					bids=ids;
				}
				//if(count>200)break;
				//cout<<"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"<<endl;
				//cout<<"obj is: "<<overflow<<" "<<toto<<" "<<objective<<endl;
				//cout<<"obj is: "<<objective<<endl;
			}
			cout<<"bestv is "<<bestv<<endl;
			return rdata;
		};*/