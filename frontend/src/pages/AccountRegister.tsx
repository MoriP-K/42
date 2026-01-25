import React, { useState } from 'react'
import { Link } from 'react-router-dom'
import Footer from '../components/Footer'
import { userApi } from '../api/userApi'
import { ApiError } from '../api/apiClient'


type RegisterError =
	| { type: 'field'; field: 'name' | 'email' | 'password'; message: string }
	| { type: 'server'; message: string }
	| { type: 'unknown'; message: string }



const AccountRegister = () => {
	const [name, setName] = useState('')
	const [email, setEmail] = useState('')
	const [password, setPassword] = useState('')
	const [passwordConfirm, setPasswordConfirm] = useState('')

	const [fieldErrors, setFieldErrors] = useState<Partial<Record<'name' | 'email' | 'password', string>>>({})
	const [serverError, setServerError] = useState<string | null>(null)

	const validateRequired = () => {
		const nextErrors: Partial<Record<'name' | 'email' | 'password', string>> = {}

		if (!email.trim())
			nextErrors.email = 'メールアドレスを入力してください'
		if (!name.trim())
			nextErrors.name = 'ユーザー名を入力してください'
		if (!password)
			nextErrors.password = 'パスワードを入力してください'

		setFieldErrors(nextErrors)
		return (Object.keys(nextErrors).length === 0)
	}

	function normalizeErrResponse(err: unknown): RegisterError {
		if (err instanceof ApiError) {
			if (err.status === 400) {
				const data = err.data as unknown
				if (typeof data === 'object' && data !== null) {
					const maybe = data as { field?: unknown; message?: unknown }
					const field = (typeof maybe.field === 'string') ? maybe.field : null
					const message = (typeof maybe.message === 'string') ? maybe.message : err.message

					if (field === 'name' || field === 'email' || field === 'password') {
						setFieldErrors((prev) => ({ ...prev, [field]: message }))
						return
					}
					setServerError(message)
					return
				}
			} else if (err.status === 500) {
				const data = err.data as unknown
				if (typeof data === 'object' && data !== null && 'message' in data) {
					setServerError(String((data as { message?: unknown }).message ?? err.message))
					return
				}
			}

			return ({
				type: 'unknown',
				message: err.message,
			})
		}
	}

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault()
		setServerError(null)
		setFieldErrors({})

		if (!validateRequired())
			return

		try {
			await userApi.register({ name, email, password })
			// NOTE: 成功時の遷移/表示は要件外なのでここでは何もしない
		} catch (err) {
			if (err instanceof ApiError) {
				const result = resolveRegisterError(err)

				switch (result.type) {
					case 'field':
						setFieldErrors((prev) => ({ ...prev, [result.field]: result.message }))
						break
					case 'server':
					case 'unknown':
						setServerError(result.message)
				}
				return
			}

			const message = (err instanceof Error) ? err.message : '予期しないエラーが発生しました'
			setServerError(message)
		}
	}

	return (
		<div className="hero min-h-screen">
			<div className="w-full max-w-md">

				<div className="text-center mb-4">
					<div className="text-2xl font-bold">アカウント新規作成</div>
				</div>

				<div className="card bg-base-200">
					<div className="card-body gap-5">

						<button type="button" className="btn btn-outline w-full">
							<span className="inline-flex items-center gap-2">
								<span className="i" aria-hidden="true">G</span>
								Googleアカウントで登録
							</span>
						</button>

						<div className="divider my-0 text-sm text-base-content/60">または</div>

						{serverError && (
							<div className="alert alert-error">
								<span>{serverError}</span>
							</div>
						)}

						<form
							className="space-y-3"
							onSubmit={handleSubmit}
						>
							<div className="form-control">
								<span className="text-base font-medium">ユーザー名</span>
								<p className="text-sm text-base-content/60">
									半角英字、数字、_を使用できます。
								</p>
								<input
									type="text"
									name="name"
									className="input input-bordered w-full"
									placeholder="例: user_name"
									autoComplete="username"
									value={name}
									onChange={(e) => setName(e.target.value)}
								/>
								{fieldErrors.name && (
									<p className="text-sm text-error">{fieldErrors.name}</p>
								)}
							</div>

							<div className="form-control">
								<span className="text-base font-medium">メールアドレス</span>
								<input
									type="text"
									name="email"
									className="input input-bordered w-full"
									placeholder="example@example.com"
									autoComplete="email"
									value={email}
									onChange={(e) => setEmail(e.target.value)}
								/>
								{fieldErrors.email && (
									<p className="text-sm text-error">{fieldErrors.email}</p>
								)}
							</div>

							<div className="form-control">
								<span className="text-base font-medium">パスワード</span>
								<p className="text-sm text-base-content/60">
									大文字・小文字・数字を組み合わせて8文字以上で入力してください。
								</p>
								<input
									type="password"
									name="password"
									className="input input-bordered w-full"
									autoComplete="new-password"
									value={password}
									onChange={(e) => setPassword(e.target.value)}
								/>
								{fieldErrors.password && (
									<p className="text-sm text-error">{fieldErrors.password}</p>
								)}
							</div>

							<div className="form-control">
								<span className="text-base font-medium">パスワード確認</span>
								<input
									type="password"
									name="passwordConfirm"
									className="input input-bordered w-full"
									autoComplete="new-password"
									value={passwordConfirm}
									onChange={(e) => setPasswordConfirm(e.target.value)}
								/>
							</div>

							<div className="space-y-2">
								<button type="submit" className="btn btn-primary w-full">
									アカウント作成
								</button>
								<Link to="/" className="btn btn-ghost w-full">
									戻る
								</Link>
							</div>
						</form>

					</div>
				</div>
				<Footer />
			</div>
		</div >
	)
}

export default AccountRegister
