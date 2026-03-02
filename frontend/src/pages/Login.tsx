import React, { useState, useEffect } from "react";
import {
	useNavigate,
	useSearchParams,
	useLocation,
	type Location,
} from "react-router-dom";
import { authApi } from "../api/authApi";
import { ApiError } from "../api/apiClient";
import { useAuth } from "../features/auth/useAuth";
import Footer from "../components/footer/Footer";
import { AuthFormShell } from "../components/auth/AuthFormShell";
import { AuthTextField } from "../components/auth/AuthTextField";
import BackButton from "../components/BackButton";
import { GoogleAccountLogin } from "../components/auth/GoogleAccountLogin";

const LOGIN_ERROR_MESSAGES: Record<string, string> = {
	invalid_request:
		"認証の有効期限が切れたか、不正なリクエストです。再度お試しください",
	account_not_found:
		"Googleアカウントが登録されていません。新規登録からお試しください",
	email_conflict:
		"このメールアドレスはすでに別の方法で登録されています。パスワードでログインしてください",
	server_error:
		"予期しないエラーが発生しました。時間をおいて再度お試しください",
};

const Login = () => {
	const navigate = useNavigate();
	const [searchParams] = useSearchParams();
	const location = useLocation();
	const { refreshAuth } = useAuth();
	const [email, setEmail] = useState("");
	const [password, setPassword] = useState("");

	const [fieldErrors, setFieldErrors] = useState<
		Partial<Record<"email" | "password", string>>
	>({});
	const [serverError, setServerError] = useState<string | null>(null);

	useEffect(() => {
		const error = searchParams.get("error");
		if (!error) return;
		const message = LOGIN_ERROR_MESSAGES[error];
		if (message) {
			queueMicrotask(() => setServerError(message));
		}
		navigate("/login", { replace: true });
	}, [searchParams, navigate]);

	const validateRequired = () => {
		const nextErrors: Partial<Record<"email" | "password", string>> = {};

		if (!email.trim())
			nextErrors.email = "メールアドレスを入力してください";
		if (!password.trim())
			nextErrors.password = "パスワードを入力してください";

		setFieldErrors(nextErrors);
		return Object.keys(nextErrors).length === 0;
	};

	const normalizeErrResponse = (err: unknown) => {
		if (!(err instanceof ApiError)) {
			return {
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
		const message = typeof body?.message === "string" ? body.message : null;

		if (message !== null) {
			return {
				message: message,
			};
		}

		return {
			message: "予期しないエラーが発生しました",
		};
	};

	const handleSubmit = async (e: React.FormEvent) => {
		e.preventDefault();
		setServerError(null);

		// 未入力チェック
		if (!validateRequired()) return;

		try {
			await authApi.login({ email, password });
			// 認証状態を更新してから遷移（Cookie反映を待つ）
			const ok = await refreshAuth();
			if (!ok) {
				setServerError("ログインに失敗しました。再度お試しください。");
				return;
			}
			const from = (location.state as { from?: Location })?.from;
			navigate(from ?? "/", { replace: true });
		} catch (err) {
			// レスポンスの正規化
			const result = normalizeErrResponse(err);
			setServerError(result.message);
		}
	};

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
						<GoogleAccountLogin />
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
						id: "email",
						type: "text",
						name: "email",
						autoComplete: "email",
						value: email,
						onChange: e => setEmail(e.target.value),
					}}
				/>

				<AuthTextField
					label="パスワード"
					htmlFor="password"
					error={fieldErrors.password}
					inputProps={{
						id: "password",
						type: "password",
						name: "password",
						autoComplete: "current-password",
						value: password,
						onChange: e => setPassword(e.target.value),
					}}
				/>
			</AuthFormShell>

			{/* TODO: 新規アカウント登録ボタン */}
			{/* フッター */}
			<Footer />
		</>
	);
};

export default Login;
