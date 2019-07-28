//Author：Meredith Ma
//Date：2019.7.28
//log模块相关的最底层类AppendFile，封装了log文件的打开、写入并在类析构时关闭文件。使用标准IO，append直接写文件
#include "FileUtil.h"
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;

AppendFile::AppendFile(std::string filename)
:   fp_(fopen(filename.c_str(), "ae"))
{
    setbuffer(fp_, buffer_, sizeof buffer_);
}

AppendFile::~AppendFile()
{
    fclose(fp_);
}

void AppendFile::append(const char *logline, size_t len)
{
    size_t n = this->write(logline, len);
    size_t remain = len - n;
    while (remain > 0) {
        size_t x = this->write(logline+n, remain);
        if (x == 0) {
            int err = ferror(fp_);
            if (err) {
                fprintf(stderr, "AppendFile::append() Failed!");
            }
            break;
        }
        n += x;
        remain = len - n;
    }
}

size_t AppendFile::write(const char *logline, size_t len)
{
    return fwrite_unlocked(logline, 1, len, fp_);
}

void AppendFile::flush()
{
    fflush(fp_);
}