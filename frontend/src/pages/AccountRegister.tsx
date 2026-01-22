import { useState } from 'react'
import { Link } from 'react-router-dom'
import Footer from '../components/Footer'

function AccountRegister() {
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
							onSubmit={(e) => {
								e.preventDefault()
								setServerError(null)

								if (!validateRequired())
									return

								// NOTE: ここでAPI送信する場合は、失敗時(500)は以下のように表示できます
								// setServerError('予期しないエラーが発生しました。時間をおいて再度お試しください')
							}}
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
