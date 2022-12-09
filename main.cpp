#include <iostream>
#include <limits>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <csignal>

void sigHandler(int sig){
    std::cout << "Неверный ввод! Попробуйте ещё раз" << std::endl;
    std::signal(SIGINT, sigHandler);
}
int inp(int a, int b) {
    int n;
    while (true){
        if (!(std::cin >> n) or n < a or n > b) {
            if (std::cin.eof()){
                return a;
            }
            std::cout << "Неверный ввод! Попробуйте ещё раз" << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else {
            return n;
        }
    }
}
std::vector <std::vector <int>> getMtrx(int M){
    std::vector <std::vector <int>> arr;
    arr.resize(M);
    std::cout << "Введите "<< M*M << " элементов" << std::endl;
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            std::cout << "Желаете ввести число сами? (1 - да, 0 - нет)" << std::endl;
            if(inp(0,1)){
                std::cout << "Введите число из диапазона [1, 100]" << std::endl;
                arr.at(i).push_back(inp(1,100));
            } else{
                arr.at(i).push_back(rand() % 100 +1);
            }
        }
    }
    return arr;
}
std::vector <int> getNsortOne(std::vector <std::vector <int>> matrix){
    std::vector <int> arr;
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (matrix[i][j]%2 == 0){
                arr.push_back(matrix[i][j]);
            }
        }
    }
    for (int i = 0; i < arr.size(); i++){
        for (int j = 0; j < arr.size()-1; j++){
            if (arr[j+1] < arr[j]){
                int t = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = t;
            }
        }
    }
    return arr;
}
std::vector <int> getNsortTwo(std::vector <std::vector <int>> matrix){
    std::vector <int> arr;
    for (int i = 0; i < matrix.size(); i++){
        for (int j = 0; j < matrix.size(); j++){
            if (matrix[i][j]%2 != 0){
                arr.push_back(matrix[i][j]);
            }
        }
    }
    for (int i = 0; i < arr.size(); i++){
        for (int j = 0; j < arr.size()-1; j++){
            if (arr[j+1] > arr[j]){
                int t = arr[j+1];
                arr[j+1] = arr[j];
                arr[j] = t;
            }
        }
    }
    return arr;
}
std::vector <int> unite(std::vector <int> part1, std::vector <int> part2){
    for (int i = 0; i < part2.size(); i++){
        part1.push_back(part2[i]);
    }
    return part1;
}
int main() {
    setlocale(0, "");
    signal(SIGINT, sigHandler);
    srand( time(0) );
    std::cout << "Введите число из диапазона [2, 5]" << std::endl;
    int M = inp(2, 5);
    std::vector <std::vector <int>> matrix = getMtrx(M);
    for (int i = 0; i < M; i++){
        for (int j = 0; j < M; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
    std::vector <int> part1 = getNsortOne(matrix);
    std::vector <int> part2 = getNsortTwo(matrix);
    std::vector <int> res = unite(part1, part2);
    std::cout << "Итоговый массив:" << std::endl;
    for (int i = 0; i < res.size(); i++){
        std::cout << res[i] << " ";
    }
    return 0;
}
