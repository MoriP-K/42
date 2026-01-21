import { Link } from 'react-router-dom'
import Footer from '../components/Footer'

function AccountRegister() {
	return (
		<div className="hero min-h-screen">
			<div div className="w-full  max-w-md" >

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

						<div className="divider my-0 text-xs text-base-content/60">または</div>

						<form
							className="space-y-3"
							onSubmit={(e) => {
								e.preventDefault()
							}}
						>
							<div className="form-control">
								<span className="text-sm font-medium">ユーザー名</span>
								<input
									type="text"
									name="name"
									className="input input-bordered w-full"
									placeholder="例: user_name"
									autoComplete="username"
								/>
								<p className="text-xs text-base-content/60">
									半角英字、数字、_を使用できます。
								</p>
							</div>

							<div className="form-control">
								<span className="text-sm font-medium">メールアドレス</span>
								<input
									type="email"
									name="email"
									className="input input-bordered w-full"
									placeholder="example@example.com"
									autoComplete="email"
								/>
							</div>

							<div className="form-control">
								<span className="text-sm font-medium">パスワード</span>
								<input
									type="password"
									name="password"
									className="input input-bordered w-full"
									autoComplete="new-password"
								/>
								<p className="text-xs text-base-content/60">
									大文字・小文字・数字を組み合わせて8文字以上で入力してください。
								</p>
							</div>

							<div className="form-control">
								<span className="text-sm font-medium">パスワード確認</span>
								<input
									type="password"
									name="passwordConfirm"
									className="input input-bordered w-full"
									autoComplete="new-password"
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
