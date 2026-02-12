import type { FormEventHandler, ReactNode } from "react";

type Props = {
	serverError?: string | null;
	onSubmit: FormEventHandler<HTMLFormElement>;
	top?: ReactNode;
	children: ReactNode;
	actions: ReactNode;
};

export function AuthFormShell({
	serverError,
	onSubmit,
	top,
	children,
	actions,
}: Props) {
	return (
		<div className="hero min-h-screen">
			<div className="w-full max-w-md">
				<div className="card bg-base-200">
					<div className="card-body gap-5">
						{top}

						{serverError && (
							<div className="alert alert-error">
								<span>{serverError}</span>
							</div>
						)}

						<form className="space-y-3" onSubmit={onSubmit}>
							{children}
							{actions}
						</form>
					</div>
				</div>
			</div>
		</div>
	);
}
