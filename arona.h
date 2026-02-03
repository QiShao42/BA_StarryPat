#ifndef ARONA_H
#define ARONA_H

// 调试模式开关 - 设置为1启用调试功能，0禁用
#define DEBUG_MODE 1

// 常用虚拟键码定义 (用于pressKey函数)
#define VK_CTRL VK_CONTROL      // Ctrl键
#define VK_SHIFT_KEY VK_SHIFT   // Shift键
#define VK_ALT_KEY VK_MENU      // Alt键
#define VK_ENTER_KEY VK_RETURN  // Enter键
#define VK_ESC VK_ESCAPE        // Esc键
#define VK_SPACE_KEY VK_SPACE   // 空格键
#define VK_TAB_KEY VK_TAB       // Tab键
#define VK_R_KEY 0x52           // R键

#include <QMainWindow>
#include <QDateTime>
#include <QMouseEvent>
#include <QTimer>
#include <QPushButton>
#include <QToolButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpacerItem>
#include <QMenuBar>
#include <QEvent>
#include <QPaintEvent>
#include <QPixmap>
#include <QComboBox>
#include <QSpinBox>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QCheckBox>
#include <QTimeEdit>
#include <QTime>
#include <QVector>
#include <QSet>
#include <QHash>
#include <QPair>
#include "timerdialog.h"
#include "studentinvitedialog.h"
#include "sweepsettingsdialog.h"
#include "aboutdialog.h"

class arona : public QMainWindow
{
    Q_OBJECT

public:
    arona(QWidget *parent = nullptr);
    ~arona();

    // 日志输出系统
    void appendLog(const QString &message, const QString &level = "INFO");
    
    // 按钮位置常量
    static const QPoint BUTTON_HALL_TO_CAFE1;
    static const QPoint BUTTON_CAFE1_TO_CAFE2;
    static const QPoint BUTTON_CAFE2_TO_CAFE1;
    static const QPoint BUTTON_INVITATION_TICKET;
    
    // 技能任务结构（定义在public以便在slots中使用）
    struct SkillTask {
        int triggerTime;        // 触发时间（毫秒）
        int releaseTime;        // 抬起时间（毫秒）
        int skillPosition;      // 技能位置：0=skill_1, 1=skill_2, 2=skill_3, -1=自动识别
        QString studentName;    // 学生名称（当skillPosition=-1时使用，用于自动识别技能位置）
        QPoint targetPosition;  // 目标位置
        bool pauseAfter;        // 释放后是否暂停
        bool isActive;          // 是否激活（用于执行中标记）
        bool isDragging;        // 是否正在拖动中（已按下但未释放）
    };

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *watched, QEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onCaptureHandleButtonPressed();
    void onCaptureHandle2ButtonPressed();
    void onCaptureHandle3ButtonPressed();
    void onSelectBgButtonClicked();
    void onstartButtonClicked();
    void onSchedulerTimerTimeout();
    void onTimerSettingsButtonClicked();
    void onStudentInviteSettingsButtonClicked();
    void onSweepSettingsButtonClicked();  // 困难扫荡设置按钮点击
    void onReloadTemplatesButtonClicked();  // 重新加载模板按钮点击
    void onLogButtonClicked();  // 执行日志按钮点击
    void onAboutButtonClicked();  // 关于按钮点击
    
#if DEBUG_MODE
    void onDebugButtonClicked();
    void onDebugTypeChanged(int index);
#endif  

private:
    // UI控件
    QWidget *centralwidget;
    QWidget *area1;
    QWidget *area2;
    QWidget *area3;
    QToolButton *logButton;
    
    QPushButton *captureHandleButton;
    QPushButton *selectBgButton;
    QPushButton *startButton;
    QLineEdit *handleLineEdit;
    QLineEdit *handleLineEdit2;
    QLineEdit *handleLineEdit3;
    QPushButton *captureHandleButton2;
    QPushButton *captureHandleButton3;
    QTextEdit *logTextEdit;
    QMenuBar *menubar;
    
    // 定时功能按钮
    QPushButton *timerSettingsButton;
    
    // 邀请学生设置按钮
    QPushButton *studentInviteSettingsButton;
    
    // 困难扫荡设置按钮
    QPushButton *sweepSettingsButton;
    
    // 重新加载模板按钮
    QPushButton *reloadTemplatesButton;
    
    // 关于按钮
    QToolButton *aboutButton;
    
#if DEBUG_MODE
    // 调试功能控件
    QGroupBox *debugGroupBox;
    QComboBox *debugTypeComboBox;
    QPushButton *debugButton;
    QWidget *clickDebugWidget;
    QLabel *clickPosLabel;
    QSpinBox *clickXSpinBox;
    QSpinBox *clickYSpinBox;
    QHBoxLayout *clickDebugLayout;
    QLabel *xLabel;
    QLabel *yLabel;
    QWidget *keyDebugWidget;
    QComboBox *keySelectComboBox;
    QHBoxLayout *keyDebugLayout;
#endif
    
    // 布局
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *verticalSpacer;
    QSpacerItem *verticalSpacer_2;
    
    // 其他成员变量
    bool isCapturingHandle;
    int capturingHandleIndex;  // 正在抓取的句柄索引（1, 2, 3）
    bool waitingForMouseRelease;  // 等待鼠标释放状态
    bool isRunning;  // 脚本是否正在运行
    bool shouldStop;  // 是否应该停止脚本
    QTimer *captureTimer;
    QTimer *schedulerTimer;  // 定时检查计时器
    QTimer *countdownTimer;  // 倒计时更新计时器
    QPixmap backgroundPixmap;  // 背景图片
    TimerDialog *timerDialog;  // 定时设置对话框
    StudentInviteDialog *studentInviteDialog;  // 邀请学生设置对话框
    SweepSettingsDialog *sweepSettingsDialog;  // 困难扫荡设置对话框
    AboutDialog *aboutDialog;  // 关于对话框
    
    // 页面管理
    int currentPage;  // 当前页面索引：0=执行日志, 1=时间捕捉
    
    // 时间数字模板
    struct TimeDigitTemplate {
        QVector<bool> binaryData;
        int width;
        int height;
    };
    QHash<QString, TimeDigitTemplate> timeDigitTemplates;  // Key格式："位置_数字"，如"M1_0"
    QSet<QRgb> validDigitColors;  // 有效的数字颜色集合（用于识别优化）
    
    // 技能图标模板哈希
    QHash<QString, QString> skillTemplateHashes;  // Key格式："学生名_位置编号"，Value=感知哈希值
    QStringList availableStudentNames;  // 可用的学生名称列表

    // 多窗口句柄
    QVector<HWND> gameHandles;  // 存储最多3个游戏窗口句柄
    QVector<QString> gameWindowTitles;  // 存储每个句柄对应的父窗口标题
    int currentHandleIndex;  // 当前正在处理的句柄索引
    
    // 定时任务
    bool timerEnabled;  // 定时功能是否启用
    QVector<TimerTaskConfig> timerTasks;  // 定时任务配置列表
    QSet<QString> executedToday;  // 今天已执行的时间（避免重复）
    QDate lastCheckDate;  // 上次检查的日期，用于判断是否跨天
    TimerTaskConfig currentTaskConfig;  // 当前正在执行的任务配置
    
    // 邀请学生列表（按窗口标题存储）
    QHash<QString, QStringList> studentInviteLists;
    
    // 困难扫荡配置（按窗口标题存储）
    QHash<QString, WindowSweepConfig> sweepConfigs;
    
    // 强制邀请设置（按窗口标题和学生名称存储，忽略衣服限制）
    // Key格式: "窗口标题|学生名称"
    QHash<QString, bool> forceInviteEnabled;

    // 位置模板哈希值
    QHash<QString, QString> positionTemplates;

    // 位置就绪模板哈希值
    QHash<QString, QString> positionReadyTemplates;

    // 特定区域
    const QRect INVITATION_TICKET_ROI = QRect(1310, 953, 36, 36);
    const QRect INVITATION_INTERFACE_ROI = QRect(623, 125, 36, 36);
    const QRect TASK_END_ROI = QRect(1840, 520, 36, 36);
    const QRect HARD_TASK_ROI = QRect(1595, 215, 36, 36);
    const QRect INVITATION_NOTICE_ROI = QRect(921, 223, 36, 36);
    const QRect EDIT_MODE_ROI = QRect(90, 992, 36, 36);
    
    // 学生头像二值化模板及尺寸信息
    struct StudentTemplate {
        QVector<bool> binaryData;
        int width;
        int height;
    };
    QHash<QString, StudentTemplate> binarizedStudentTemplates;
    
    // 辅助函数
    void setupUi();
    void setBackgroundImage(const QString &imagePath);
    
    void captureWindowHandle(int handleIndex);
    HWND findGameWindowByParentTitle(const QString &parentTitle);  // 根据父窗口标题查找游戏窗口

    QImage captureWindow(HWND hwnd);
    QString calculateImageHash(const QImage& image, const QRect& roi = QRect());
    void loadPositionTemplates();
    void loadpositionReadyTemplates();
    void loadStudentAvatarTemplates();

    QString recognizeCurrentPosition(QImage screenshot, QString targetPosition);
    void checkAndExecuteScheduledTasks();
    void executeAllWindows();
    bool isPositionReady(QImage screenshot, QRect roi);
    QString checkNotice(QImage screenshot, QRect roi);
    bool refreshCafe(HWND hwnd);
    
    // 参数保存/加载
    void saveTimerSettings();   // 保存定时参数到配置文件
    void loadTimerSettings();   // 从配置文件加载定时参数
    void saveStudentInviteSettings();   // 保存邀请学生设置到配置文件
    void loadStudentInviteSettings();   // 从配置文件加载邀请学生设置
    void saveSweepSettings();   // 保存困难扫荡设置到配置文件
    void loadSweepSettings();   // 从配置文件加载困难扫荡设置
    void saveWindowHandles();   // 保存窗口句柄信息到配置文件
    void loadWindowHandles();   // 从配置文件加载窗口句柄信息并自动查找窗口
    
    // 窗口标题管理
    QStringList getValidWindowTitles() const;  // 获取所有有效的窗口标题列表
    void updateStudentInviteDialog();  // 更新邀请学生对话框的窗口列表
    
    // 工具函数
    void sweepTask(HWND hwnd, QString titleStr);
    bool inviteStudentToCafe(HWND hwnd, QString titleStr, int cafeNumber);  // cafeNumber: 1=咖啡厅1, 2=咖啡厅2
    void muteSound(HWND hwnd);
    void doTask(HWND hwnd, int taskIndex, int subTaskIndex);
    void delayMs(int milliseconds);  // 无阻塞延时
    bool delayMsWithCheck(int milliseconds);  // 带停止检查的延时，返回false表示需要停止
    void click(HWND hwnd, int x, int y);  // 模拟点击
    void clickGrid(HWND hwnd, int x1, int y1, int x2, int y2, int spacing = 50, int delay = 20);  // 地毯式点击
    void moveMouse(int x, int y);  // 移动真实鼠标到屏幕坐标
    void moveMouseToWindow(HWND hwnd, int x, int y);  // 移动真实鼠标到窗口坐标
    void drag(HWND hwnd, int startX, int startY, int endX, int endY, int duration = 500);  // 拖动
    void dragSkill(HWND hwnd, int startX, int startY, int endX, int endY);  // 技能释放专用拖动（只负责按下和拖动）
    void releaseSkill(HWND hwnd, int x, int y);  // 释放技能（发送鼠标抬起）
    void scroll(HWND hwnd, int x, int y, int delta);  // 模拟滚轮 (delta>0向上滚, delta<0向下滚)
    void pressKey(HWND hwnd, int vkCode, bool press);  // 按键控制 (press=true按下, press=false抬起)
    void pressKeyGlobal(int vkCode, bool press);  // 全局按键控制（不需要窗口句柄）
    
    // 脚本控制函数
    void startScript();  // 启动脚本
    void stopScript();  // 停止脚本
    void updateStartButtonState();  // 更新启动按钮状态
    void executeScript(HWND hwnd, QString titleStr);  // 执行脚本主逻辑
    
    // 业务逻辑函数
    void enterCafe1FromHall(HWND hwnd);
    void enterCafe2FromCafe1(HWND hwnd);
    void enterCafe1FromCafe2(HWND hwnd);
    bool inviteStudentByName(HWND hwnd, QStringList studentNames, QString titleStr);
    int findStudentInInvitationInterface(QImage image, QString studentName);
    bool compareImagesByOddRows(const QImage &image1, const QImage &image2);  // 逐像素对比奇数行（已废弃）
    QVector<bool> binarizeImage(const QImage &image, const QRgb &backgroundColor);  // 二值化图像
    int calculateHammingDistance(const QVector<bool> &binary1, const QVector<bool> &binary2);  // 计算汉明距离
    bool compareImagesByHamming(const QImage &image, const QVector<bool> &templateBinary, int width, int height, const QRgb &backgroundColor, double threshold = 0.95);  // 基于汉明距离的图像比较
    
    // 辅助逻辑函数（封装重复逻辑）
    bool waitForPosition(HWND hwnd, const QString &targetPosition, int maxRetries, int delayMs, int clickX, int clickY);
    bool adjustCafeView(HWND hwnd, int scrollX, int scrollY, int scrollCount = 12);
    void adjustCafePosition(HWND hwnd);
    void patStudents(HWND hwnd, int rounds = 3);
    void closeGameWindow(HWND hwnd);
    void closeGameWindowByReturn(HWND hwnd);
    
#if DEBUG_MODE
    // 调试功能函数
    void screenshotDebug();
    void clickDebug();
    void keyDebug();
#endif
};
#endif // ARONA_H
