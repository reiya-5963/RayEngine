﻿#pragma once

//#include "MyMath.h"
#include <Windows.h>
#include <array>
#include <vector>
#include <wrl.h>

#include <Xinput.h>
#define DIRECTINPUT_VERSION	0x0800 // DirectInputのバージョン指定
#include <dinput.h>

/// <summary>
/// 入力クラス
/// </summary>
class Input {
public:
	/// <summary>
	/// シングルトンインスタンスの取得
	/// </summary>
	/// <returns>シングルトンインスタンス</returns>
	static Input* GetInstance();

	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// キーが押されているかどうか
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>押されているか</returns>
	bool PushKey(BYTE keyNumber) const;

	/// <summary>
	/// キーが1フレームのみ押されているかどうか
	/// </summary>
	/// <param name="keyNumber">キー番号</param>
	/// <returns>トリガーか</returns>
	bool TriggerKey(BYTE keyNumber) const;

	/// <summary>
	/// 全キー情報取得
	/// </summary>
	/// <returns>マウス情報</returns>
	const std::array<BYTE, 256>& GetAllKey() const { return key_; }

	/// <summary>
	/// マウス押しているかどうか
	/// </summary>
	/// <param name="mouseNumber">マウス番号(0:左, 1:右, 2:中, 3~7:拡張)</param>
	/// <returns>押されているかどうか</returns>
	bool IsPressMouse(int32_t mouseNumber) const;

	/// <summary>
	/// マウストリガーチェック
	/// </summary>
	/// <param name="mouseNumber">マウス番号(0:左, 1:右, 2:中, 3~7:拡張)</param>
	/// <returns>押されているかどうか</returns>
	bool IsTriggerMouse(int32_t mouseNumber) const;

	/// <summary>
	/// 全マウス情報取得
	/// </summary>
	/// <returns>マウス情報</returns>
	const DIMOUSESTATE2& GetAllMouse() const;

	/// <summary>
	/// ホイールスクロール量の取得
	/// </summary>
	/// <returns>ホイールスクロール量</returns>
	int32_t GetWhieel() const;

private:
	Input() = default;
	~Input();
	Input(const Input&) = delete;
	const Input& operator=(const Input&) = delete;

private: // メンバ関数
	Microsoft::WRL::ComPtr<IDirectInput8> directinput_;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> deviceKeyboard_;
	Microsoft::WRL::ComPtr<IDirectInputDevice8> deviceMouse_;

	std::array<BYTE, 256> key_;
	std::array<BYTE, 256> preKey_;

	DIMOUSESTATE2 mouse_;
	DIMOUSESTATE2 preMouse_;

	HWND hwnd_;

};