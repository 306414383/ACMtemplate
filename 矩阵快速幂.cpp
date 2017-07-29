#define siz 6
#define Mytype int
int N=6;
Mytype mod;
struct matrix
{
	Mytype a[siz][siz];
	matrix operator*(const matrix &y)const
	{
		matrix res;
		mem(res.a,0);
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				if(a[i][j])
					for(int k=0;k<N;k++)
						res.a[i][k]+=a[i][j]*y.a[j][k],res.a[i][k]%=mod;
		return res;
	}
	matrix operator+(const matrix &y)const
	{
		matrix res;
		for(int i=0;i<N;i++)
			for(int j=0;j<N;j++)
				res.a[i][j]=a[i][j]+y.a[i][j],res.a[i][j]%=mod;
		return res;
	}
	matrix operator*=(const matrix &y)
	{
		*this=y* *this;
		return *this;
	}
};
matrix qmod(matrix a,int k)
{
	matrix res;
	mem(res.a,0);
	for(int i=0;i<N;i++)
		res.a[i][i]=1;
	while(k)
	{
		if(k&1)
			res*=a;
		a*=a;
		k>>=1;
	}
	return res;
}
