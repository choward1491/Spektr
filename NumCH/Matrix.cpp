
#include "Matrix.h"
#include <math.h>


int abs(int c)
{
	if (c < 0)
		return -c;
	return c;
}



    

//Matrix constructors
Matrix::Matrix(int r, int c, int flag = GEN, bool transpose = false)
{
	rows = r;
	cols = c;
	type = flag;
	T = transpose;
	int N = 0;
	switch (type)
	{
	case GEN:
		N = r*c;
		break;
	case DIAG:
		N = r;
		break;
	case TDIAG:
		N = 3 * r - 2;
		break;
	case SYM:
		N = r*(r + 1) / 2;
	case UTRI:
	case LTRI:
		break;
	case SPARSE:
		N = 1;
		break;
	default:
		N = r*c;
		break;
	}

	mat = new double[N];
	for (int i = 0; i < N; i++)
		mat[i] = 0;
}
Matrix::Matrix(string matrix)
{
    int ncolon=0, ncomma=0;
    int numL=0, numR=0;
    char number[30];
    if(matrix.empty()){
        
    }else{
        //cout << ncolon <<", "<< ncomma << endl;
        char cc;
        
        for(int i=0; i<matrix.length(); i++)
        {
            cc = matrix[i];
            //cout << cc;
            if( cc == '[' || cc == '(' )
                numL++;
            else if( cc == ']' || cc == ']' )
                numR++;
            else if( cc == ';')
                ncolon++;
            else if( cc == ',')
                ncomma++;
        }
        //cout << endl;
        
        rows = ncolon+1;
        cols = ncomma/ncolon;
        int N = rows*cols;
        
        T = false;
        type = GEN;
        //cout << N<<endl;
        mat = new double[N];
        int ii = 1;
        int ind = 0;
        int ploc = -1;
        bool c1, c2, c3;
        int c = 1;
        for(int i=0; i < N; i++)
        {
            mat[i] = 0;
            ploc = -1; ind = 0; c = 1;
            while( 1 ){
                cc = matrix[ii];
                c1 = cc <= '9';
                c2 = cc >= '0';
                c3 = cc == '.';
                if( cc == ',' || cc == ';' || cc == ']'){
                    ii++;
                    break;
                }
                else if( (c1 && c2) || c3 )
                {
                    if( c3 && ploc == -1 ){
                        ploc = ind; number[ind] = cc; ind++;
                    }else if(c1 && c2){
                        number[ind] = cc; ind++;
                    }
                }else if( cc == '-' ){
                    c = -1;
                }
                ii++;
            }
            
            number[ind] = '\0';
            //cout << number << endl;
            if( ploc < 0 )
            {
                double factor = 1.0;
                
                for(int k=ind-1; k>=0; k--){
                    mat[i] += factor*(number[k]-'0');
                    factor = factor*10;
                }
            }else{
                double factor = 1.0;
                
                for(int k=ploc-1; k>=0; k--){
                    mat[i] += factor*(number[k]-'0');
                    factor = factor*10;
                }
                factor = .1;
                for(int k=ploc+1; k<ind; k++){
                    mat[i] += factor*(number[k]-'0');
                    factor = factor*.1;
                }
            }
            
            mat[i] = c*mat[i];
        }
    }
    
    
}
Matrix::Matrix(const Matrix & m)
{
	//clear();
	copy(m);
}

//Matrix operators
double Matrix::operator()(int r, int c) const
{
	//Assume r = 0,1,...,rows-1 are valid
	//Assume c = 0,1,...,cols-1 are valid
	if (T)
	{
		int t = c;
		c = r;
		r = t;
	}
	int v = 0;
	switch (type)
	{
	case GEN:
		return mat[r*cols + c];
		break;

	case DIAG:
		if (r != c)
			return double(0);
		else
			return mat[r];
		break;
	case TDIAG: //Data holds +1 diag, then 0 diag, then -1 diag
		v = r - c;
		if (abs(v) > 1)
			return tmp;
		else{
			if (v == -1)       //+1 diagonal
				return mat[r];
			else if (v == 0)   //0 diagonal
				return mat[(rows - 1) + r];
			else               //-1 diagonal
				return mat[2 * (rows - 1) + r];
		}
		break;
	case SYM:
		if (r > c)
		{
			int tmp = r;
			r = c;
			c = tmp;
		}

		return mat[r*rows + c - (r*(r + 1)) / 2];
		
		break;
	case UTRI:
		
		if (r > c)
			return 0;
		else
			return mat[r*rows + c - (r*(r + 1)) / 2];
		break;
	case LTRI:
		if (c > r)
			return 0;
		else{
			return mat[c*rows + r - (c*(c + 1)) / 2];
		}
		break;
	case SPARSE:

		break;
	default:

		break;
	}

	return double(0);

}
double & Matrix::operator()(int r, int c)
{
	//Assume r = 0,1,...,rows-1 are valid
	//Assume c = 0,1,...,cols-1 are valid
	if (T)
	{
		int t = c;
		c = r;
		r = t;
	}
	int v = 0;
	switch (type)
	{
	case GEN:
		return mat[r*cols + c];
		break;
	case DIAG:
		if (r != c)
			return tmp;
		else
			return mat[r];
		break;
	case TDIAG: //Data holds +1 diag, then 0 diag, then -1 diag
		v = r - c;
		if (abs(v) > 1)
			return tmp;
		else{
			if (v == -1)      //+1 diagonal
				return mat[r];
			else if (v == 0) //0 diagonal
				return mat[(rows - 1) + r];
			else               //-1 diagonal
				return mat[2 * (rows - 1) + r];
		}
		break;
	case SYM:
		if (r > c)
		{
			int t = r;
			r = c;
			c = t;
		}


		return mat[r*rows + c - (r*(r + 1)) / 2];

		break;
	case UTRI:

		if (r > c)
			return tmp;
		else
			return mat[r*rows + c - (r*(r + 1)) / 2];
		break;
	case LTRI:
		if (c > r)
			return tmp;
		else{
			return mat[c*rows + r - (c*(c + 1)) / 2];
		}
		break;
	case SPARSE:

		break;
	default:

		break;
	}

	return tmp;
}

double Matrix::operator()(int k) const
{
	return mat[k];
}
double & Matrix::operator()(int k)
{
	return mat[k];
}

Matrix Matrix::operator*(const Matrix & M) const
{
	if (cols != M.getRows())
		return Matrix();
	int r1 = rows, c = cols, c2 = M.getCols();
	Matrix m(r1, c2, GEN, false);
	for (int i = 0; i < r1; i++)
	{
		for (int j = 0; j < c2; j++)
		{
			for (int k = 0; k < c; k++)
			{
				m(i, j) += (*this)(i, k)*M(k, j);
			}
		}
	}

	return m;
}
Matrix Matrix::operator+(const Matrix & m) const
{
	if (rows == m.getRows() && cols == m.getCols())
	{
		if (type == m.type)
		{
			Matrix M(rows, cols, type);
			for (int i = 0; i < rows*cols; i++)
				M(i) = mat[i] + m(i);
			return M;
		}
	}
	return Matrix();
}
Matrix Matrix::operator-(const Matrix & m) const
{
	if (rows == m.getRows() && cols == m.getCols())
	{
		if (type == m.type)
		{
			Matrix M(rows, cols, type);
			for (int i = 0; i < rows*cols; i++)
				M(i) = mat[i] - m(i);
			return M;
		}
	}
	return Matrix();
}
void Matrix::operator=(const Matrix & m)
{
	if (this != &m)
	{
		clear();
		copy(m);
	}
}


//Special matrix functionality
double Matrix::determinant() const
{
	switch (type)
	{
	case GEN:
		break;
	case DIAG:
	{
				 double det = 1;
				 for (int i = 0; i < rows; i++)
					 det *= mat[i];
				 return det;
	}
		break;
	case TDIAG: //Data holds +1 diag, then 0 diag, then -1 diag
		
		break;
	case SYM:

		break;
	case UTRI:

		break;
	case LTRI:

		break;
	case SPARSE:

		break;
	default:

		break;
	}
	return double();
}
Matrix Matrix::invert()
{
	switch (type)
	{
	case GEN:
		
		break;
	case DIAG:
	{
				 Matrix M(rows, cols, DIAG);
				 for (int i = 0; i < rows; i++)
					 M(i) = 1.0 / mat[i];
				 return M;
	}
		break;
	case TDIAG: //Data holds +1 diag, then 0 diag, then -1 diag
	{
				Matrix M(rows, cols, TDIAG);
				
				 for (int i = 0; i < rows; i++)
					 M(i) = 1.0 / mat[i];
				 return M;
	}
		break;
	case SYM:
	{

	}
		break;
	case UTRI:
	{

	}
		break;
	case LTRI:
	{

	}
		break;
	case SPARSE:

		break;
	default:

		break;
	}
	return Matrix();
}


void Matrix::print() const
{
	if (mat == 0)
		return;
	if (T)
	{
		for (int i = 0; i < cols; i++)
		{
			cout << "| " << (*this)(i, 0);
			for (int j = 1; j < rows; j++)
			{
				cout << ", " << (*this)(i, j);
			}
			cout << " |\n";
		}
	}
	else{
		for (int i = 0; i < rows; i++)
		{
			cout << "| " << (*this)(i, 0);
			for (int j = 1; j < cols; j++)
			{
				cout << ", " << (*this)(i, j);
			}
			cout << " |\n";
		}
	}
	cout << "\n";
}

void Matrix::clear()
{
    if( mat != 0 )
        delete[] mat;
	mat = 0;
	rows = 0;
	cols = 0;
	type = -1;
}
void Matrix::copy( const Matrix & m)
{
	rows = m.getRows();
	cols = m.getCols();
	type = m.getType();
    T=m.getTranspose();
    
	
	int N = rows*cols;
	mat = new double[N];
	for (int i = 0; i < N; i++)
		mat[i] = m(i);

}

Matrix solve(Matrix & A, Matrix & b, int flag)
{
	int r = A.getRows();
	int c = A.getCols();
	int cn = b.getRows();
	if (r == c && cn == c){
		int type = A.getType();
		switch (type)
		{
		case GEN:

			break;
		case DIAG:
		{
					 Matrix M(r, 1, GEN);
					 for (int i = 0; i < r; i++)
						 M(i) = b(i) / A(i);
					 return M;
		}
			break;
		case TDIAG: //Data holds +1 diag, then 0 diag, then -1 diag

			break;
		case SYM:

			break;
		case UTRI:

			break;
		case LTRI:

			break;
		case SPARSE:

			break;
		default:

			break;
		}
	}
	return Matrix();
}
Matrix gaussElim(Matrix & A, Matrix & b)
{
	return Matrix();
}

Matrix linspace(double xs, double xe, int N)
{
	double dx = (xe - xs) / (double)(N - 1);
	Matrix m(N, 1, GEN, false);
	for (int i = 0; i < N; i++)
		m(i) = xs + i*dx;
	return m;
}
double Matrix::mag()
{
    int N = rows*cols;
    if( N > 0 )
    {
        double mag = 0;
        for(int i=0; i<N; i++)
            mag = mag + mat[i]*mat[i];
        mag = sqrt(mag);
        return mag;
    }
    
    return -1;
    
}

double sign(double val)
{
    if(val < 0)
        return -1;
    else
        return 1;
}

void Matrix::normalize()
{
    double N = rows*cols;
    if( N > 0 )
    {
        double mag = 0;
        for(int i=0; i<N; i++)
            mag = mag + mat[i]*mat[i];
        mag = sqrt(mag);
        for(int i=0; i<N; i++)
            mat[i] = mat[i] / mag;
    }
}

void Matrix::QR_Decomposition(Matrix &Q, Matrix &R) const
{
    if( rows == cols && rows > 0 )
    {
        double alpha;
        R.doCopy( (*this) );
        Matrix Qi(rows,cols, GEN, false);
        Matrix m(rows,rows,GEN,false);
        
        for( int iter=0; iter < cols-1; iter++ )
        {
            int l = rows-iter;
            Matrix v(l,1,GEN,false);
            for(int i=iter; i<rows; i++)
                v(i-iter)=R(i, iter);
            alpha = -sign(v(0))*v.mag();
            v(0) = v(0) + alpha;
            v.normalize();
            Matrix b(l,l,GEN,false);
            for(int i=0; i<l; i++){
                for(int j=0; j<l; j++){
                    b(i,j) = -2*v(i)*v(j);
                }
            }
            
            //Find transform Qi
            for(int i = 0; i < rows; i++ ){
                for( int j = 0 ; j< rows; j++ )
                {
                    Qi(i,j) = (i==j);
                    if( i >= iter && j >= iter ){
                        Qi(i,j) = Qi(i,j) + b(i-iter,j-iter);
                    }
                }
            }
            //Qi.print();
            if( iter == 0 )
                Q=Qi;
            else{
                //Q=Qi*Q;
                
                for (int i = 0; i < rows; i++)
                {
                    for (int j = 0; j < rows; j++)
                    {
                        m(i,j) = 0;
                        for (int k = 0; k < rows; k++)
                        {
                            m(i, j) += Qi(i, k)*Q(k, j);
                        }
                    }
                }
                Q=m;
            }
            
            for (int i = 0; i < rows; i++)
            {
                for (int j = 0; j < rows; j++)
                {
                    m(i,j) = 0;
                    for (int k = 0; k < rows; k++)
                    {
                        m(i, j) += Qi(i, k)*R(k, j);
                    }
                }
            }
            R=m;
        }
            Q.transpose();

    }
}
void Matrix::eig( Matrix & eigenvalues, Matrix & eigenvectors) const
{
    if( rows == cols && cols > 0 ){
        Matrix Q(rows,rows,GEN,false),R(rows,rows,GEN,false);
        Matrix Qi(rows,rows,GEN,false);
        Matrix D((*this));
        int iter = 0;
        while( fabs(D(1,0)) > 1e-6 ){
            D.QR_Decomposition(Qi, R);
            D = R*Qi;
            if( iter > 0 )
                Q=Q*Qi;
            else
                Q=Qi;
            iter++;
            Qi.transpose();
        }
        //cout << "Number of iterations is "<<iter<<endl;
        //D.print();
        for(int i=0; i<rows; i++)
            eigenvalues(i,i)=D(i,i);
        eigenvectors = Q;
    }
}

Matrix Matrix::squareRoot() const
{
    if( rows == cols && rows > 0 ){
        Matrix L(rows,rows,DIAG,false), Q(rows,rows,GEN,false);
        (*this).eig(L,Q);
        int chck = 0;
        for(int i=0; i<rows; i++)
        {
            if( L(i) <= 0 && chck == 0){
                cout << "There are problems with the eigenvalues. They aren't positive, so you need to look into this. Will use absolute value of eigenvalue for now\n";
                L(i) = -L(i);
                chck++;
            }
            L(i) = sqrt(L(i));
        }
        Matrix B=Q*L; Q.transpose();
        B=B*Q;
        return B;
    }else{
        return Matrix();
    }
}

