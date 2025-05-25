#define _USE_MATH_DEFINES
#include <vector>
#include <random>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

int main(){
    std::vector<int> c, C, Pi, Pm;
    std::vector<double> alpha;
    std::ifstream fin1("tasks.csv");
    std::string line;
    std::getline(fin1, line);
    while(std::getline(fin1, line)){
        std::stringstream ss(line);
        std::string id, cpu;
        std::getline(ss, id, ',');
        std::getline(ss, cpu, ',');
        c.push_back(std::stoi(cpu));
    }
    fin1.close();
    std::ifstream fin2("vms.csv");
    std::getline(fin2, line);
    while(std::getline(fin2, line)){
        std::stringstream ss(line);
        std::string id, cpu, idle, maxp, scale;
        std::getline(ss, id, ',');
        std::getline(ss, cpu, ',');
        std::getline(ss, idle, ',');
        std::getline(ss, maxp, ',');
        std::getline(ss, scale, ',');
        C.push_back(std::stoi(cpu));
        Pi.push_back(std::stoi(idle));
        Pm.push_back(std::stoi(maxp));
        alpha.push_back(std::stod(scale));
    }
    fin2.close();
    int n = c.size(), m = C.size(), pop = 40, T = 200;
    std::mt19937_64 rng(0);
    std::uniform_real_distribution<> du(0.0,1.0);
    auto energy = [&](const std::vector<double>& X){
        std::vector<int> A(n);
        for(int i=0;i<n;++i) A[i] = std::clamp(int(std::round(X[i])), 0, m-1);
        double E=0;
        for(int j=0;j<m;++j){
            double sum=0;
            for(int i=0;i<n;++i) if(A[i]==j) sum += c[i];
            if(sum>0){
                double u = sum / C[j];
                double f = alpha[j];
                double pi = Pi[j] * f;
                double pm = Pm[j] * f;
                E += pi + (pm - pi) * u;
            }
        }
        return E;
    };
    std::uniform_real_distribution<> dx(0.0, m-1.0);
    std::vector<std::vector<double>> X(pop, std::vector<double>(n));
    std::vector<double> F(pop);
    for(int i=0;i<pop;++i){
        for(int k=0;k<n;++k) X[i][k] = dx(rng);
        F[i] = energy(X[i]);
    }
    int bi = std::min_element(F.begin(), F.end()) - F.begin();
    auto B = X[bi];
    double best = F[bi];
    for(int t=0;t<T;++t){
        double a = 2 * (1.0 - double(t) / T);
        for(int i=0;i<pop;++i){
            double r1 = du(rng), r2 = du(rng), p = du(rng);
            double A = 2 * a * r1 - a;
            double Cc = 2 * r2;
            for(int k=0;k<n;++k){
                if(p < 0.5){
                    if(std::abs(A) < 1){
                        double D = std::abs(Cc * B[k] - X[i][k]);
                        X[i][k] = B[k] - A * D;
                    } else {
                        auto& R = X[rng() % pop];
                        double D = std::abs(Cc * R[k] - X[i][k]);
                        X[i][k] = R[k] - A * D;
                    }
                } else {
                    double D = std::abs(B[k] - X[i][k]);
                    double l = std::uniform_real_distribution<>(-1.0,1.0)(rng);
                    X[i][k] = D * std::exp(l) * std::cos(2 * M_PI * l) + B[k];
                }
                X[i][k] = std::clamp(X[i][k], 0.0, m-1.0);
            }
        }
        for(int i=0;i<pop;++i){
            double v = energy(X[i]);
            if(v < best){ best = v; B = X[i]; }
        }
    }
    std::cout << "Optimal Energy: " << best << "\nAssignments: ";
    for(int i=0;i<n;++i) std::cout << int(std::round(B[i])) << " ";
    std::cout << "\n";
    return 0;
}
