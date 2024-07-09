$bytes = [System.IO.File]::ReadAllBytes((Join-Path -Path $PSScriptRoot -ChildPath "\Shaders011.fxp"))
$sb = [System.Text.StringBuilder]::new()

for ($i = 0; $i -lt $bytes.Length; $i++) {
	if ($i % 16 -eq 0) {
		[void]$sb.Append("`r`n")
	}
		
	[void]$sb.Append(($bytes[$i] -bxor 0x56).ToString())

	if ($i -lt $bytes.Length - 1) {
		[void]$sb.Append(", ")
	}
}

$headerContent = `
@"
#pragma once

const static unsigned char ShaderPackageBinaryBlobXorKey = 0x56; // See ShaderPackageStream::DoRead

const static inline unsigned char ShaderPackageBinaryBlob[] = {$($sb.ToString())`r`n};
"@

# Then write it back to disk
$headerContent | Out-File -FilePath (Join-Path -Path $PSScriptRoot -ChildPath "\..\Source\Impl\ShaderPackageBinaryBlob.inl") -Encoding ASCII