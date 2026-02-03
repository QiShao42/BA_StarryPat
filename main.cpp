/*
 * BAStarryPat - Blue Archive Automation Tool
 * Copyright (c) 2026 星空的诺言
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 * 
 * GitHub: https://github.com/QiShao42/BAStarryPat
 * 
 * DISCLAIMER: This software is provided for educational purposes only.
 * Use at your own risk. May violate game Terms of Service.
 */

#include "arona.h"

#include <QApplication>
#include <QIcon>
#include <QFont>
#include <QLockFile>
#include <QDir>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 单实例检查：防止同时运行多个程序实例
    QString lockFilePath = QDir::temp().absoluteFilePath("arona_single_instance.lock");
    QLockFile lockFile(lockFilePath);
    lockFile.setStaleLockTime(0); // 立即检测陈旧锁
    
    if (!lockFile.tryLock(100)) {
        // 无法获取锁，说明已有实例在运行
        QMessageBox msgBox;
        msgBox.setIcon(QMessageBox::Warning);
        msgBox.setWindowTitle("程序已在运行");
        msgBox.setText("检测到程序已经在运行中！");
        msgBox.setInformativeText("同一时间只能运行一个程序实例。\n\n"
                                  "如果您确定没有其他实例在运行，请检查任务管理器。");
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
        return 1; // 退出程序
    }

    // 设置全局字体
    // QFont font("Source Han Sans", 10);
    // QFont font("Microsoft YaHei UI", 10);
    QFont font("PingFang SC", 10);
    a.setFont(font);
    
    // 设置应用程序图标（任务栏和窗口图标）
    a.setWindowIcon(QIcon(":/images/icon/app_icon.png"));
    
    arona w;
    w.show();
    return a.exec();
}
