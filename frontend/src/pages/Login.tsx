import React, { useState } from 'react'
import { useNavigate } from 'react-router-dom'
import { authApi } from '../api/authApi'
import { ApiError } from '../api/apiClient'
import Footer from "../components/footer/Footer"
import { AuthFormShell } from '../components/auth/AuthFormShell'
import { AuthTextField } from '../components/auth/AuthTextField'
import BackButton from '../components/BackButton'

const Login = () => {
	const navigate = useNavigate();
	const [email, setEmail] = useState('')
	const [password, setPassword] = useState('')

	const [fieldErrors, setFieldErrors] = useState<Partial<Record<'email' | 'password', string>>>({})
	const [serverError, setServerError] = useState<string | null>(null)

	const validateRequired = () => {
		const nextErrors: Partial<Record<'email' | 'password', string>> = {}

		if (!email.trim())
			nextErrors.email = 'メールアドレスを入力してください'
		if (!password.trim())
			nextErrors.password = 'パスワードを入力してください'

		setFieldErrors(nextErrors)
		return (Object.keys(nextErrors).length === 0)
	}

	const normalizeErrResponse = (err: unknown) => {
		if (!(err instanceof ApiError)) {
			return {
				message: err instanceof Error ? err.message : '予期しないエラーが発生しました',
			}
		}

		const body = typeof err.data === 'object' && err.data !== null ? (err.data as { field?: unknown; message?: unknown }) : null
		const message = typeof body?.message === 'string' ? body.message : null

		if (message !== null) {
			return {
				message: message,
			}
		}

		return {
			message: '予期しないエラーが発生しました',
		}
	}

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault()
		setServerError(null)

		// 未入力チェック
		if (!validateRequired())
			return

		try {
			await authApi.login({ email, password })
			//TODO: トーストの表示
			//TODO: 元々アクセスしようとしていたページに戻す(?)
			navigate('/');
		} catch (err) {
			// レスポンスの正規化
			const result = normalizeErrResponse(err)
			setServerError(result.message)
		}
	}

	return (
		<>
			{/* ヘッダー */}
			{/* TODO: ゲームタイトル */}
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">ログイン画面</span>
			</div>

			{/* 記入フォーム */}
			<AuthFormShell
				serverError={serverError}
				onSubmit={handleSubmit}
				top={
					<>
						<button type="button" className="btn btn-outline w-full">
							{/* TODO: Googleアカウントでログイン処理*/}
							<span className="inline-flex items-center gap-2">
								<span className="i" aria-hidden="true">G</span>
								Googleアカウントでログイン
							</span>
						</button>
						<div className="divider my-0 text-sm text-base-content/60">または</div>
					</>
				}
				actions={
					<div className="space-y-2">
						<button type="submit" className="btn btn-primary w-full">
							ログイン
						</button>
						<BackButton></BackButton>
					</div>
				}
			>
				<AuthTextField
					label="メールアドレス"
					htmlFor="email"
					error={fieldErrors.email}
					inputProps={{
						id: 'email',
						type: 'text',
						name: 'email',
						autoComplete: 'email',
						value: email,
						onChange: (e) => setEmail(e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード"
					htmlFor="password"
					error={fieldErrors.password}
					inputProps={{
						id: 'password',
						type: 'password',
						name: 'password',
						autoComplete: 'current-password',
						value: password,
						onChange: (e) => setPassword(e.target.value),
					}}
				/>

			</AuthFormShell>

			{/* TODO: 新規アカウント登録ボタン */}
			{/* フッター */}
			<Footer />
		</>
	)
}

export default Login
