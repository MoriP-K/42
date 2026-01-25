import type { InputHTMLAttributes } from 'react'

type Props = {
	label: string
	description?: string
	error?: string
	inputProps: InputHTMLAttributes<HTMLInputElement>
}

export function AuthTextField({ label, description, error, inputProps }: Props) {
	return (
		<div className="form-control">
			<span className="text-base font-medium">
				{label}
			</span>

			{description && (
				<p className="text-sm text-base-content/60">{description}</p>
			)}

			<input
				{...inputProps}
				className="input input-bordered w-full"
			/>

			{error && <p className="text-sm text-error">{error}</p>}
		</div>
	)
}

