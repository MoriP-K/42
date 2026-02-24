import Footer from "../components/footer/Footer";
import React, { useState, useMemo } from "react";
import { authApi } from "../api/authApi";
import { ApiError } from "../api/apiClient";
import { AuthFormShell } from "../components/auth/AuthFormShell";
import { AuthTextField } from "../components/auth/AuthTextField";
import { GoogleAccountRegister } from "../components/auth/GoogleAccountRegister";
import BackButton from "../components/BackButton";
import { useNavigate } from "react-router-dom";

type RegisterError =
	| { type: "field"; field: "name" | "email" | "password"; message: string }
	| { type: "server"; message: string }
	| { type: "unknown"; message: string };

type RegisterField = "name" | "email" | "password" | "passwordConfirm";
type FormErrors = Partial<Record<RegisterField, string>>;

/** バックエンドと同一のルールでフォームを検証 */
const validateRegisterForm = (
	name: string,
	email: string,
	password: string,
	passwordConfirm: string,
): { valid: boolean; errors: FormErrors } => {
	const errors: FormErrors = {};

	if (!name.trim()) {
		errors.name = "ユーザー名を入力してください";
	} else if (!/^[a-z0-9_]+$/.test(name)) {
		errors.name = "ユーザー名には半角英数字と「_」のみ使用できます";
	}

	if (!email.trim()) {
		errors.email = "メールアドレスを入力してください";
	} else if (
		!/^[a-zA-Z0-9.!#$%&'*+/=?^_`{|}~-]+@[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?(?:\.[a-zA-Z0-9](?:[a-zA-Z0-9-]{0,61}[a-zA-Z0-9])?)*$/.test(
			email,
		)
	) {
		errors.email = "メールアドレスの形式が正しくありません";
	}

	if (!password.trim()) {
		errors.password = "パスワードを入力してください";
	} else if (password.length < 8) {
		errors.password = "パスワードは8文字以上で入力してください";
	} else if (
		!/[A-Z]/.test(password) ||
		!/[a-z]/.test(password) ||
		!/[0-9]/.test(password)
	) {
		errors.password =
			"パスワードには英大文字・英小文字・数字をそれぞれ1文字以上含めてください";
	}

	if (!passwordConfirm.trim()) {
		errors.passwordConfirm = "パスワード確認を入力してください";
	} else if (password !== passwordConfirm) {
		errors.passwordConfirm = "パスワードが一致しません";
	}

	return {
		valid: Object.keys(errors).length === 0,
		errors,
	};
};

const AccountRegister = () => {
	const navigate = useNavigate();
	const [name, setName] = useState("");
	const [email, setEmail] = useState("");
	const [password, setPassword] = useState("");
	const [passwordConfirm, setPasswordConfirm] = useState("");

	const [touched, setTouched] = useState<
		Partial<Record<RegisterField, boolean>>
	>({});
	const [serverError, setServerError] = useState<string | null>(null);
	const [submitErrors, setSubmitErrors] = useState<FormErrors>({});

	const validationResult = useMemo(
		() => validateRegisterForm(name, email, password, passwordConfirm),
		[name, email, password, passwordConfirm],
	);

	const isFormValid = validationResult.valid;

	const fieldErrorsToShow: FormErrors = useMemo(() => {
		const result: FormErrors = {};
		for (const field of [
			"name",
			"email",
			"password",
			"passwordConfirm",
		] as const) {
			const err = submitErrors[field] ?? validationResult.errors[field];
			if (err && touched[field]) {
				result[field] = err;
			}
		}
		return result;
	}, [validationResult.errors, touched, submitErrors]);

	const setFieldTouched = (field: RegisterField) => {
		setTouched(prev => ({ ...prev, [field]: true }));
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
		setSubmitErrors({});

		if (!validationResult.valid) {
			setTouched({
				name: true,
				email: true,
				password: true,
				passwordConfirm: true,
			});
			setSubmitErrors(validationResult.errors);
			return;
		}

		try {
			await authApi.register({ name, email, password });
			navigate("/");
		} catch (err) {
			const result = normalizeErrResponse(err);

			if (result.type === "field") {
				setTouched(prev => ({ ...prev, [result.field]: true }));
				setSubmitErrors(prev => ({
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
						<GoogleAccountRegister />
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
							disabled={!isFormValid}
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
					error={fieldErrorsToShow.name}
					inputProps={{
						id: "name",
						type: "text",
						name: "name",
						placeholder: "例: user_name",
						autoComplete: "username",
						value: name,
						onChange: e => setName(e.target.value),
						onBlur: () => setFieldTouched("name"),
					}}
				/>

				<AuthTextField
					label="メールアドレス"
					htmlFor="email"
					error={fieldErrorsToShow.email}
					inputProps={{
						id: "email",
						type: "text",
						name: "email",
						placeholder: "example@example.com",
						autoComplete: "email",
						value: email,
						onChange: e => setEmail(e.target.value),
						onBlur: () => setFieldTouched("email"),
					}}
				/>

				<AuthTextField
					label="パスワード"
					htmlFor="password"
					description="大文字・小文字・数字を組み合わせて8文字以上で入力してください。"
					error={fieldErrorsToShow.password}
					inputProps={{
						id: "password",
						type: "password",
						name: "password",
						autoComplete: "new-password",
						value: password,
						onChange: e => setPassword(e.target.value),
						onBlur: () => setFieldTouched("password"),
					}}
				/>

				<AuthTextField
					label="パスワード確認"
					htmlFor="passwordConfirm"
					error={fieldErrorsToShow.passwordConfirm}
					inputProps={{
						id: "passwordConfirm",
						type: "password",
						name: "passwordConfirm",
						autoComplete: "new-password",
						value: passwordConfirm,
						onChange: e => setPasswordConfirm(e.target.value),
						onBlur: () => setFieldTouched("passwordConfirm"),
					}}
				/>
			</AuthFormShell>

			{/* フッター */}
			<Footer />
		</>
	);
};

export default AccountRegister;
