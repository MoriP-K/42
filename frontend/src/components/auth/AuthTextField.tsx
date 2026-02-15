import type { InputHTMLAttributes } from 'react'

type Props = {
	label: string
	htmlFor: string
	description?: string
	error?: string
	inputProps: InputHTMLAttributes<HTMLInputElement>
}

export function AuthTextField({ label, htmlFor, description, error, inputProps }: Props) {
	return (
		<div className="form-control">
			<label htmlFor={htmlFor} className="text-base font-medium">
				{label}
			</label>

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

