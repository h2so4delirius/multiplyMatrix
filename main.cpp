#include <cassert>
#include <iostream>
#include <fstream>


double * matrixMultiply(unsigned int height_1, unsigned int width_1, unsigned int height_2, unsigned int width_2, double * matrix_1, double * matrix_2){
    if(width_1!=height_2){
        return nullptr;
    }
    double * result = new double[width_2*height_1]; 
    for (unsigned int i = 0; i < height_1 * width_2; ++i)
        result[i] = 0.0;
    for (unsigned int i = 0; i < height_1; ++i) {
        for (unsigned int j = 0; j < width_2; ++j) {
            for (unsigned int k = 0; k < width_1; ++k) {   
                result[i * width_2 + j] +=
                    matrix_1[i * width_1 + k] * matrix_2[k * width_2 + j];
            }
        }
    }
    return result;
}

void ShowMatrix(double *matrix, unsigned int height, unsigned int weight){
    for(unsigned int i = 0; i < height * weight; i++){
        std::cout<< matrix[i] << " ";
        if(((i + 1) % weight) == 0){std::cout<< std::endl;}
    }
    std::cout<< std::endl;
    return;
}

bool almostEqual(double a, double b) {
    return a == b;
}


void writeInFile(double *matrix, unsigned int height, unsigned int weight){
    std::ofstream out;
    out.open("result.txt");
    if (out.is_open())
    {
        out <<height<<" "<<weight<<std::endl;
        for (unsigned int i = 0; i < height; i++){
            for (unsigned int j = 0; j < weight; j++){
                out<<matrix[i * weight + j]<<" ";
            }
            out<<std::endl;
        }
    }
    out.close();    
    return;
}

double* readMatrix(const std::string& filename,unsigned int& height,unsigned int& weight) {
    std::ifstream fin(filename);
    if (!fin.is_open()) {
        throw std::runtime_error("Cannot open file: "+filename);
    }
    fin >> height >> weight;
    double*arr = new double[height * weight];
    for (int i = 0; i < height * weight; i++) {
        fin >> arr[i];
    }
    return arr;
}




int main(){
        double *A = new double[1]{2.0};
        double *B =new double[1]{3.0};
        double* C = matrixMultiply(1, 1, 1, 1, A, B);
        assert(almostEqual(C[0], 6.0));
        delete[] A;
        delete[] B;
        delete[] C;
        A = new double[6]{1, 2, 3,
                       4, 5, 6};
        B = new double[6]{7, 8,
                       9, 10,
                       11, 12};
        double expected[4] = {58, 64, 139, 154};
        C = matrixMultiply(2, 3, 3, 2, A, B);
        for (int i = 0; i < 4; i++)
            assert(almostEqual(C[i], expected[i]));
        delete[] A;
        delete[] B;
        delete[] C;
        A = new double[9]{1, 2, 3,
                       4, 5, 6,
                       7, 8, 9};
        double *I = new double[9]{1, 0, 0,
                       0, 1, 0,
                       0, 0, 1};
        C = matrixMultiply(3, 3, 3, 3, A, I);
        for (int i = 0; i < 9; i++)
            assert(almostEqual(C[i], A[i]));
        delete[] A;
        delete[] I;
        delete[] C;
        I = new double[36] {0};
        for (int i = 0; i < 6; i++)
            I[i * 6 + i] = 1.0;

        double *M = new double[36];
        for (int i = 0; i < 36; i++)
            M[i] = i + 1; // 1..36

        C = matrixMultiply(6, 6, 6, 6, I, M);
        for (int i = 0; i < 36; i++)
            assert(almostEqual(C[i], M[i]));
        ShowMatrix(C,6,6);
        delete[] M;
        delete[] I;
        delete[] C;
        A = new double[12]{1, 2,
                        3, 4,
                        5, 6,
                        7, 8,
                        9, 10,
                        11, 12};

        B = new double[12]{1, 2, 3, 4, 5, 6,
                        7, 8, 9, 10, 11, 12};


        double expected_2[36] = {15,18,	21,	24, 27,	30,
                                31,	38,	45,	52,	59,	66,
                                47,	58,	69,	80,	91,	102,
                                63,	78,	93,	108,	123,	138,
                                79,	98,	117,	136,	155,	174,
                                95	,118	,141	,164	,187	,210};
    
        C = matrixMultiply(6, 2, 2, 6, A, B);

        ShowMatrix(C,6,6);
        for (int i = 0; i < 36; i++)
            assert(almostEqual(C[i], expected_2[i]));
        delete[] A;
        delete[] B;
        delete[] C;

        A = new double[6]{1, 2,
                       3, 4,
                       5, 6};
        B = new double[10]{1, 2, 3, 4, 5,
                        6, 7, 8, 9, 10};
        double expected_3[15] = {
            13,16,19,22,25,
            27,34,41,48,55,
            41,52,63,74,85
        };

        C = matrixMultiply(3, 2, 2, 5, A, B);
        ShowMatrix(C,3,5);
        for (int i = 0; i < 15; i++)
            assert(almostEqual(C[i], expected_3[i]));
        writeInFile(C,3,5);
        delete[] A;
        delete[] B;
        delete[] C;
        unsigned int height,weight;
        A = readMatrix("result.txt",height,weight);
        ShowMatrix(A,height,weight);
        delete[] A;

        std::cout << "All matrixMultiply tests passed!\n";
        return 0;
}
