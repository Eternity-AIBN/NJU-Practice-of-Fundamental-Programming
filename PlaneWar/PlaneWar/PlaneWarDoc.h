
// PlaneWarDoc.h : CPlaneWarDoc 类的接口
//


#pragma once
#include"GameRun.h"

class CPlaneWarDoc : public CDocument
{
protected: // 仅从序列化创建
	CPlaneWarDoc();
	DECLARE_DYNCREATE(CPlaneWarDoc)

	// 特性
public:

	// 操作
public:
	const CImage& getBackground() const { return background; }
	int getHeight() { return gameRun.getHeight(); }
	int getWidth() { return gameRun.getWidth(); }
	void playerMove(int act) { gameRun.playerMove(act); }
	void launchBullet() { gameRun.launchBullet(); }  //发射子弹
	void updateBullets() { gameRun.updateBullets(); }
	void updateEnemies() { gameRun.updateEnemies(); }
	bool isGameOver() { return gameRun.gameOver(); }
	void init() { gameRun.init(); }
	const MyPlane &getPlanePlayer() const { return gameRun.getPlanePlayer(); }
	const vector<Enemy> &getEnemy() const { return gameRun.getEnemy(); }
	const vector<Bullet> &getBullet() const { return gameRun.getBullet(); }
	int getScore() const { return gameRun.getScore(); }

	// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

	// 实现
public:
	virtual ~CPlaneWarDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	GameRun gameRun;
	CImage background;

	// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
