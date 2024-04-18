#ifndef REPLACE_WITH_YOUR_PROJECT_NAME_RANDOMFACTORY_HPP
#define REPLACE_WITH_YOUR_PROJECT_NAME_RANDOMFACTORY_HPP

#include <cstdlib> /* 亂數相關函數 */
#include <ctime>   /* 時間相關函數 */

class RandomFactory{
public:

    RandomFactory()=default;


    int GenerateRandomNumber(int input) {
        // 使用随机数引擎生成器和分布器
        srand( time(nullptr) );

        /* 指定亂數範圍 */
        int min = 1;
        int max = input;

        /* 產生 [min , max] 的整數亂數 */
        return rand() % (max - min + 1) + min;
    };

};

#endif //REPLACE_WITH_YOUR_PROJECT_NAME_RANDOMFACTORY_HPP
