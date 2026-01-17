import TermsOfServiceContent from "../components/TermsOfServiceContent"

function TermsOfService() {
  return (
    <div className="min-h-screen bg-base-200">
      <div className="navbar bg-base-100 shadow-lg">
        <div className="flex-1">
          <a className="btn btn-ghost text-xl">🎨 おえかきの森</a>
        </div>
      </div>

      <div className="hero min-h-[80vh]">
        <div className="hero-content text-center">
          <div className="max-w-md">
            <h1 className="text-5xl font-bold">！利用規約！</h1>
            {/* <React.StrictMode> */}
				<TermsOfServiceContent>
				</TermsOfServiceContent>
			{/* </React.StrictMode> */}
          </div>
        </div>
      </div>
    </div>
  )
}

export default TermsOfService
