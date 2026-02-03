#include "aboutdialog.h"
#include <QFont>
#include <QTextBrowser>

AboutDialog::AboutDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUi();
}

AboutDialog::~AboutDialog()
{
}

void AboutDialog::setupUi()
{
    // 设置对话框属性
    this->setWindowTitle("关于");
    this->setMinimumSize(500, 600);
    this->setMaximumSize(500, 600);
    
    // 创建主布局
    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    
    // 标题标签
    titleLabel = new QLabel("星空摸头机", this);
    QFont titleFont;
    titleFont.setPointSize(20);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: #2196F3; padding: 10px; }");
    mainLayout->addWidget(titleLabel);
    
    // 版本信息
    versionLabel = new QLabel("版本: 1.0.2", this);
    QFont versionFont;
    versionFont.setPointSize(11);
    versionLabel->setFont(versionFont);
    versionLabel->setAlignment(Qt::AlignCenter);
    versionLabel->setStyleSheet("QLabel { color: #666; padding: 5px; }");
    mainLayout->addWidget(versionLabel);
    
    // 免责声明区域
    QLabel *disclaimerTitleLabel = new QLabel("免责声明", this);
    QFont sectionFont;
    sectionFont.setPointSize(12);
    sectionFont.setBold(true);
    disclaimerTitleLabel->setFont(sectionFont);
    disclaimerTitleLabel->setStyleSheet("QLabel { color: #333; padding: 5px 0; }");
    mainLayout->addWidget(disclaimerTitleLabel);
    
    disclaimerTextEdit = new QTextEdit(this);
    disclaimerTextEdit->setReadOnly(true);
    disclaimerTextEdit->setStyleSheet("QTextEdit { "
                                      "background-color: #f5f5f5; "
                                      "border: 1px solid #ddd; "
                                      "border-radius: 5px; "
                                      "padding: 10px; "
                                      "font-size: 10pt; "
                                      "}");
    disclaimerTextEdit->setHtml(
        "<p style='margin:5px 0;'><b>本软件仅供学习和研究使用，不得用于任何商业用途。</b></p>"
        "<p style='margin:5px 0;'>本软件按&quot;现状&quot;提供，不提供任何明示或暗示的保证，包括但不限于适销性、特定用途的适用性和非侵权性的保证。</p>"
        // "<p style='margin:5px 0;'>使用本软件所产生的一切后果均由使用者自行承担，开发者不承担任何法律责任。</p>"
        // "<p style='margin:5px 0;'><b style='color:#d32f2f;'>警告：</b>使用本软件可能违反游戏服务条款。请在充分了解风险后谨慎使用。</p>"
        // "<p style='margin:5px 0;'>本软件可能存在bug或不稳定情况。</p>"
    );
    disclaimerTextEdit->setMaximumHeight(180);
    mainLayout->addWidget(disclaimerTextEdit);
    
    // 版权声明区域
    QLabel *copyrightTitleLabel = new QLabel("版权声明", this);
    copyrightTitleLabel->setFont(sectionFont);
    copyrightTitleLabel->setStyleSheet("QLabel { color: #333; padding: 5px 0; }");
    mainLayout->addWidget(copyrightTitleLabel);
    
    copyrightTextEdit = new QTextBrowser(this);
    copyrightTextEdit->setReadOnly(true);
    copyrightTextEdit->setOpenExternalLinks(true);  // QTextBrowser支持此方法
    copyrightTextEdit->setStyleSheet("QTextEdit { "
                                     "background-color: #f5f5f5; "
                                     "border: 1px solid #ddd; "
                                     "border-radius: 5px; "
                                     "padding: 10px; "
                                     "font-size: 10pt; "
                                     "}");
    copyrightTextEdit->setHtml(
        "<p style='margin:5px 0;'><b>Copyright © 2026 星空的诺言</b></p>"
        // "<p style='margin:5px 0;'>本软件基于 <b>GNU General Public License v3.0</b> (GPL-3.0) 开源许可证发布。</p>"
        // "<p style='margin:5px 0;'><b style='color:#4CAF50;'>✓</b> 允许自由使用、复制、修改和分发</p>"
        // "<p style='margin:5px 0;'><b style='color:#4CAF50;'>✓</b> 允许用于商业目的（但必须开源）</p>"
        // "<p style='margin:5px 0;'><b style='color:#FF9800;'>⚠</b> 任何衍生作品必须采用相同的GPL v3许可证</p>"
        // "<p style='margin:5px 0;'><b style='color:#FF9800;'>⚠</b> 禁止将本代码用于闭源商业产品</p>"
        // "<p style='margin:5px 0;'>详见：<a href='https://github.com/QiShao42/BAStarryPat' style='color:#2196F3;'>GitHub仓库</a> | <a href='https://www.gnu.org/licenses/gpl-3.0.html' style='color:#2196F3;'>GPL v3全文</a></p>"
        "<p style='margin:8px 0 5px 0;'><b>第三方组件：</b></p>"
        "<p style='margin:3px 0 3px 15px;'>• Qt Framework (LGPL v3) - © The Qt Company</p>"
        "<p style='margin:3px 0 3px 15px;'>• 游戏素材、截图、商标归《蔚蓝档案》及其开发商 NEXON 所有</p>"
        "<p style='margin:3px 0 3px 15px;'>• 部分图标、背景图素材来自第三方创作者或AI生成</p>"
        "<p style='margin:5px 0;'><b>本软件与《蔚蓝档案》官方无任何关联，非官方授权产品。</b></p>"
    );
    copyrightTextEdit->setMaximumHeight(230);
    copyrightTextEdit->setOpenExternalLinks(true);  // 允许打开外部链接
    mainLayout->addWidget(copyrightTextEdit);
    
    // 添加弹簧
    mainLayout->addStretch();
    
    // 关闭按钮
    closeButton = new QPushButton("关闭", this);
    closeButton->setMinimumHeight(35);
    closeButton->setStyleSheet("QPushButton { "
                               "background-color: #2196F3; "
                               "color: white; "
                               "border: none; "
                               "border-radius: 5px; "
                               "font-size: 11pt; "
                               "font-weight: bold; "
                               "padding: 5px; "
                               "} "
                               "QPushButton:hover { "
                               "background-color: #1976D2; "
                               "} "
                               "QPushButton:pressed { "
                               "background-color: #0D47A1; "
                               "}");
    mainLayout->addWidget(closeButton);
    
    // 连接关闭按钮信号
    connect(closeButton, &QPushButton::clicked, this, &QDialog::accept);
}
