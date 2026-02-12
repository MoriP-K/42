import Footer from "../components/footer/Footer";
import React, { useState } from "react";
import { authApi } from "../api/authApi";
import { ApiError } from "../api/apiClient";
import { AuthFormShell } from "../components/auth/AuthFormShell";
import { AuthTextField } from "../components/auth/AuthTextField";
import BackButton from "../components/BackButton";
import { useNavigate } from "react-router-dom";

type RegisterError =
	| { type: "field"; field: "name" | "email" | "password"; message: string }
	| { type: "server"; message: string }
	| { type: "unknown"; message: string };

const AccountRegister = () => {
	const navigate = useNavigate();
	const [name, setName] = useState("");
	const [email, setEmail] = useState("");
	const [password, setPassword] = useState("");
	const [passwordConfirm, setPasswordConfirm] = useState("");

	const [fieldErrors, setFieldErrors] = useState<
		Partial<
			Record<"name" | "email" | "password" | "passwordConfirm", string>
		>
	>({});
	const [serverError, setServerError] = useState<string | null>(null);

	const validateRequired = () => {
		const nextErrors: Partial<
			Record<"name" | "email" | "password" | "passwordConfirm", string>
		> = {};

		if (!email.trim())
			nextErrors.email = "メールアドレスを入力してください";
		if (!name.trim()) nextErrors.name = "ユーザー名を入力してください";
		if (!password.trim())
			nextErrors.password = "パスワードを入力してください";
		if (!passwordConfirm.trim())
			nextErrors.passwordConfirm = "パスワード確認を入力してください";
		if (password !== passwordConfirm)
			nextErrors.passwordConfirm = "パスワードが一致しません";

		setFieldErrors(nextErrors);
		return Object.keys(nextErrors).length === 0;
	};

	const normalizeErrResponse = (err: unknown): RegisterError => {
		if (!(err instanceof ApiError)) {
			return {
				type: "unknown",
				message:
					err instanceof Error
						? err.message
						: "予期しないエラーが発生しました",
			};
		}

		const body =
			typeof err.data === "object" && err.data !== null
				? (err.data as { field?: unknown; message?: unknown })
				: null;
		const field = typeof body?.field === "string" ? body.field : null;
		const message = typeof body?.message === "string" ? body.message : null;

		if (err.status === 400 && field !== null && message !== null) {
			if (field === "name" || field === "email" || field === "password") {
				return {
					type: "field",
					field: field,
					message: message,
				};
			}
		}

		if (err.status === 500 && message !== null) {
			return {
				type: "server",
				message: message,
			};
		}

		return {
			type: "unknown",
			message: "予期しないエラーが発生しました",
		};
	};

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setServerError(null);
		setFieldErrors({});

		// 未入力チェック・パスワード一致確認
		if (!validateRequired()) return;

		try {
			await authApi.register({ name, email, password });
			navigate("/");
		} catch (err) {
			// レスポンスの正規化
			const result = normalizeErrResponse(err);

			if (result.type === "field") {
				setFieldErrors(prev => ({
					...prev,
					[result.field]: result.message,
				}));
			} else {
				setServerError(result.message);
			}
		}
	};

	return (
		<>
			{/* ヘッダー */}
			<div className="text-center mb-4">
				<span className="text-2xl font-bold">アカウント新規作成</span>
			</div>

			{/* 記入フォーム */}
			<AuthFormShell
				serverError={serverError}
				onSubmit={handleSubmit}
				top={
					<>
						<button
							type="button"
							className="btn btn-outline w-full"
						>
							{/* TODO: Googleアカウントで登録処理*/}
							<span className="inline-flex items-center gap-2">
								<span className="i" aria-hidden="true">
									G
								</span>
								Googleアカウントで登録
							</span>
						</button>
						<div className="divider my-0 text-sm text-base-content/60">
							または
						</div>
					</>
				}
				actions={
					<div className="space-y-2">
						<button
							type="submit"
							className="btn btn-primary w-full"
						>
							アカウント作成
						</button>
						<BackButton></BackButton>
					</div>
				}
			>
				<AuthTextField
					label="ユーザー名"
					htmlFor="name"
					description="半角英字、数字、_を使用できます。"
					error={fieldErrors.name}
					inputProps={{
						id: "name",
						type: "text",
						name: "name",
						placeholder: "例: user_name",
						autoComplete: "username",
						value: name,
						onChange: e => setName(e.target.value),
					}}
				/>

				<AuthTextField
					label="メールアドレス"
					htmlFor="email"
					error={fieldErrors.email}
					inputProps={{
						id: "email",
						type: "text",
						name: "email",
						placeholder: "example@example.com",
						autoComplete: "email",
						value: email,
						onChange: e => setEmail(e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード"
					htmlFor="password"
					description="大文字・小文字・数字を組み合わせて8文字以上で入力してください。"
					error={fieldErrors.password}
					inputProps={{
						id: "password",
						type: "password",
						name: "password",
						autoComplete: "new-password",
						value: password,
						onChange: e => setPassword(e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード確認"
					htmlFor="passwordConfirm"
					error={fieldErrors.passwordConfirm}
					inputProps={{
						id: "passwordConfirm",
						type: "password",
						name: "passwordConfirm",
						autoComplete: "new-password",
						value: passwordConfirm,
						onChange: e => setPasswordConfirm(e.target.value),
					}}
				/>
			</AuthFormShell>

			{/* フッター */}
			<Footer />
		</>
	);
};

export default AccountRegister;
