
// gzipToolsDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gzipTools.h"
#include "gzipToolsDlg.h"
#include "ErrorMessage.h"

#ifdef __cplusplus
extern "C"
{
#include "zlib/gzip.h"
}
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CgzipToolsDlg �Ի���




CgzipToolsDlg::CgzipToolsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CgzipToolsDlg::IDD, pParent)
        , m_strSrcPath(_T(""))
        , m_strDstPath(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CgzipToolsDlg::DoDataExchange(CDataExchange* pDX)
{
        CDialog::DoDataExchange(pDX);
        DDX_Text(pDX, EDT_SRCPATH, m_strSrcPath);
        DDV_MaxChars(pDX, m_strSrcPath, 260);
        DDX_Text(pDX, EDT_DSTPATH, m_strDstPath);
	DDV_MaxChars(pDX, m_strDstPath, 260);
}

BEGIN_MESSAGE_MAP(CgzipToolsDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
        ON_BN_CLICKED(BTN_SRCBROW, &CgzipToolsDlg::OnBnClickedSrcbrow)
        ON_BN_CLICKED(BTN_DSTBROW, &CgzipToolsDlg::OnBnClickedDstbrow)
        ON_BN_CLICKED(BTN_COMPRESS, &CgzipToolsDlg::OnBnClickedCompress)
        ON_BN_CLICKED(BTN_UNCOMPRESS, &CgzipToolsDlg::OnBnClickedUncompress)
END_MESSAGE_MAP()


// CgzipToolsDlg ��Ϣ�������

BOOL CgzipToolsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
        // ��ʼ��״̬��
        m_StatusBar.Create(WS_CHILD | WS_VISIBLE, CRect(0,0,0,0), this, 101) ;
        int arWidth[2] = {260,-1} ;
        m_StatusBar.SetParts(2, arWidth) ;
        wchar_t szKernelName[MAX_PATH] = {0} ;

        m_StatusBar.SetText(TEXT("Copyright(c)2015 EvilKnight ����"),0,0) ;

        GetDlgItem(BTN_COMPRESS)->EnableWindow(FALSE) ;
        GetDlgItem(BTN_UNCOMPRESS)->EnableWindow(FALSE) ;

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CgzipToolsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CgzipToolsDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CgzipToolsDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CgzipToolsDlg::OnCancel()
{
        // TODO: �ڴ����ר�ô����/����û���

        CDialog::OnCancel();
}

void CgzipToolsDlg::OnOK()
{
        // TODO: �ڴ����ר�ô����/����û���

        CDialog::OnOK();
}

BOOL CgzipToolsDlg::PreTranslateMessage(MSG* pMsg)
{
        // TODO: �ڴ����ר�ô����/����û���
        if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_ESCAPE)
                return TRUE;
        if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
                return TRUE;

        return CDialog::PreTranslateMessage(pMsg);
}

void CgzipToolsDlg::OnBnClickedSrcbrow()
{
        // TODO: �ڴ���ӿؼ�֪ͨ����������
        CFileDialog dlg(TRUE,
                NULL,
                NULL,
                OFN_HIDEREADONLY,
                TEXT("All Files (*.*)|*.*||"),
                AfxGetMainWnd());

        if (dlg.DoModal()==IDOK)
        {
                m_strSrcPath = dlg.GetPathName();
                UpdateData(FALSE) ;
                GetDlgItem(BTN_COMPRESS)->EnableWindow(TRUE) ;
                GetDlgItem(BTN_UNCOMPRESS)->EnableWindow(TRUE) ;
        }
}

void CgzipToolsDlg::OnBnClickedDstbrow()
{
        // TODO: �ڴ���ӿؼ�֪ͨ����������
        CFileDialog dlg(TRUE,
                NULL,
                NULL,
                OFN_HIDEREADONLY,
                TEXT("All Files (*.*)|*.*||"),
                AfxGetMainWnd());

        if (dlg.DoModal()==IDOK)
        {
                m_strDstPath = dlg.GetPathName();
                UpdateData(FALSE) ;
        }

}

void CgzipToolsDlg::OnBnClickedCompress()
{
        // TODO: �ڴ���ӿؼ�֪ͨ����������
        gzipStream(false) ;
}

void CgzipToolsDlg::OnBnClickedUncompress()
{
        // TODO: �ڴ���ӿؼ�֪ͨ����������
        gzipStream(true) ;
}

/*******************************************************************************
*
*   �� �� �� : gzipStream
*  �������� : gzipѹ�����ѹ����,��������ʽ
*  �����б� : bMode       --  ����ģʽ
*  ˵      �� :  bModeΪfalseʱΪѹ������ģʽ��bModeΪtrueΪ��ѹ����ģʽ
*  ���ؽ�� :  ��������ɹ�������0, ʧ�ܷ���-1(��ѹ��ѹ�����Ϊ����ֵ)
*
*******************************************************************************/
int CgzipToolsDlg::gzipStream(bool bMode)
{
        UpdateData(TRUE) ;

        HANDLE hSrcFile = INVALID_HANDLE_VALUE ;
        HANDLE hDstFile = INVALID_HANDLE_VALUE ;
        DWORD dwError(0) ;
        DWORD dwFileSize(0) ;
        DWORD dwNeedBufSize(0) ;
        PBYTE pSrcBuffer(NULL), pDstBuffer(NULL) ;
        DWORD dwNumberOfBytesRead(0) ;
        DWORD dwNumberOfBytesWritten(0);
        int nResult(-1) ;
        BOOL bWriteFileRresult(false) ;

        __try
        {
                hSrcFile = CreateFile(m_strSrcPath.GetBuffer(0),
                                                        GENERIC_READ,
                                                        FILE_SHARE_READ,
                                                        NULL,
                                                        OPEN_EXISTING,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL) ;

                if (INVALID_HANDLE_VALUE == hSrcFile)
                {
                        dwError = GetLastError() ;
                        OutputDebugString(TEXT("create srcfile failed!\r\n")) ;
                        __leave ;
                }

                // ���û��ָ��Ŀ��·�����Լ�����һ��
                if (m_strDstPath.GetLength() == 0)
                {
                        m_strDstPath = m_strSrcPath ;
                        m_strDstPath += TEXT(".out") ;
                        UpdateData(FALSE) ;
                }

                hDstFile = CreateFile(m_strDstPath.GetBuffer(0),
                                                        GENERIC_WRITE,
                                                        FILE_SHARE_WRITE,
                                                        NULL,
                                                        OPEN_ALWAYS,
                                                        FILE_ATTRIBUTE_NORMAL,
                                                        NULL) ;

                if (INVALID_HANDLE_VALUE == hDstFile)
                {
                        dwError = GetLastError() ;
                        OutputDebugString(TEXT("create desfile failed!\r\n")) ;
                        __leave ;
                }

                dwFileSize = GetFileSize(hSrcFile, NULL) ;

                pSrcBuffer = new Byte[dwFileSize] ;

                if (NULL == pSrcBuffer)
                {
                        OutputDebugString(TEXT("malloc memory failed!\r\n")) ;
                        __leave ;
                }

                if ( ! ReadFile(hSrcFile, pSrcBuffer, dwFileSize,&dwNumberOfBytesRead , NULL)
                        ||  dwNumberOfBytesRead == 0)
                {
                        OutputDebugString(TEXT("ReadFile failed!\r\n")) ;
                        __leave ;
                }

                // bModeΪtrue�Ļ�Ϊ��ѹģʽ������һ��Ŀռ�
                // ��ʵѹ���Ļ����ڴ���������ٵ�
                dwNeedBufSize = dwFileSize * (bMode?8:2) ;
                pDstBuffer = new Byte[dwNeedBufSize] ;

                if (bMode)
                {
                        nResult = httpgzdecompress(pSrcBuffer,
                                                                        dwFileSize,
                                                                        pDstBuffer,
                                                                        &dwNeedBufSize) ;
                }
                else
                {
                        nResult = gzcompress(pSrcBuffer,
                                                                dwFileSize,
                                                                pDstBuffer,
                                                                &dwNeedBufSize) ;
                }
                
                if (-1 != nResult)
                {
                        bWriteFileRresult = WriteFile(hDstFile,
                                                                                pDstBuffer,
                                                                                dwNeedBufSize,
                                                                                &dwNumberOfBytesWritten, 
                                                                                NULL) ;
                }
                else
                {
                        m_StatusBar.SetText(bMode?TEXT("��ѹ���ݳ���"):TEXT("ѹ�����ݳ���"),1,0) ;
                        __leave ;
                }

                // д���ļ��ɹ�
                if (bWriteFileRresult && dwNumberOfBytesWritten == dwNeedBufSize)
                {
                        m_StatusBar.SetText(bMode?TEXT("��ѹ���ݳɹ����ɹ�д���ļ�")
                                                                         :TEXT("ѹ�����ݳɹ����ɹ�д���ļ�"),1,0) ;
                }
                else
                {
                        m_StatusBar.SetText(bMode?TEXT("��ѹ���ݳɹ�����д���ļ�ʧ��")
                                                                         :TEXT("ѹ�����ݳɹ�����д���ļ�ʧ��"),1,0) ;
                }
                
        }

        __finally
        {
                if (INVALID_HANDLE_VALUE != hSrcFile)
                {
                        CloseHandle(hSrcFile) ;
                        hSrcFile = INVALID_HANDLE_VALUE ;
                }

                if (INVALID_HANDLE_VALUE != hDstFile)
                {
                        CloseHandle(hDstFile) ;
                        hDstFile = INVALID_HANDLE_VALUE ;
                }

                if (NULL != pSrcBuffer)
                {
                        delete [] pSrcBuffer ;
                        pSrcBuffer = NULL ;
                }

                if (NULL != pDstBuffer)
                {
                        delete [] pDstBuffer ;
                        pDstBuffer = NULL ;
                }
        }

        return nResult ;
}
