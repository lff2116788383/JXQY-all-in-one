
// hot_update.cpp
#include <iostream>
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <curl/curl.h>
#include "iniReader.h"
using namespace std;

// 定义回调函数，用于将下载的数据写入本地文件
size_t write_callback(void *ptr, size_t size, size_t nmemb, void *stream) {
    return fwrite(ptr, size, nmemb, (FILE *)stream);
}

// 子函数，用于下载网络文件到本地
int download_file(const char *url, const char *output_filename) {
    CURL *curl = curl_easy_init();
    FILE *fp = fopen(output_filename, "wb");  // 打开一个文件用于保存下载的数据

    if (curl && fp) {
        // 设置下载选项
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        // 执行下载请求
        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "下载失败: %s\n", curl_easy_strerror(res));
            fclose(fp);
            curl_easy_cleanup(curl);
            return -1;
        }

        fclose(fp);
    } else {
        fprintf(stderr, "初始化失败\n");
        if (fp) {
            fclose(fp);
        }
        if (curl) {
            curl_easy_cleanup(curl);
        }
        return -1;
    }

    curl_easy_cleanup(curl);
    return 0;
}

int main() {
    ini::iniReader ini_reader;
    string hot_update_ini="hot_update.ini";
    if(!ini_reader.ReadConfig(hot_update_ini)){
        printf("热更配置文件丢失\n");
    }
    string hot_update_server_domain = ini_reader.ReadString("init", "hot_update_server_domain", "null");
    string hot_update_server_ip = ini_reader.ReadString("init", "hot_update_server_ip", "null");
    int hot_update_server_port=ini_reader.ReadInt("init", "hot_update_server_port", 0);

    printf("hot_update_server_domain:%s, hot_update ip:%s, port:%d\n", hot_update_server_domain.c_str(), hot_update_server_ip.c_str(), hot_update_server_port);

    string url="http://"+ hot_update_server_ip + ":" + to_string(hot_update_server_port) + "/Version-220302151834/Windows/common/audio/bgm.ab";
    // const char *url = "http://example.com/file.zip";
    const char *output_filename = "bgm.ab";
    printf("download url:%s\n", url.c_str());
    int ret = download_file(url.c_str(), output_filename);
    if (ret == 0) {
        printf("文件下载成功！\n");
    } else {
        printf("文件下载失败！\n");
    }

    return 0;
}


// int main(int argc, char *argv[]){
// // 从ini配置获取资源服务器地址
// // 1.获取服务器资源的md5
// // 2.对比本地资源md5
// // 3.下载替换本地资源


// 	return 0;
// }
//g++ hot_update.cpp -o hot_update -std=c++11 -lcurl 
