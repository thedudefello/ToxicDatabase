# PowerShell script (publish-all.ps1)
function Get-AssemblyVersion {
    param (
        [string]$configuration = "Release",
        [string]$runtime = ""
    )
    
    # First try to get version from .csproj file
    $csprojFiles = Get-ChildItem -Filter "*.csproj"
    if ($csprojFiles.Count -gt 0) {
        $csprojContent = Get-Content $csprojFiles[0]
        $versionLine = $csprojContent | Where-Object { $_ -match '<AssemblyVersion>(.*)</AssemblyVersion>' } | Select-Object -First 1
        if ($versionLine -match '<AssemblyVersion>(\d+\.\d+\.\d+)\.(\d+)</AssemblyVersion>') {
            $version = $matches[1]
            if ($matches[2] -ne "0") {
                $version = "$version.$($matches[2])"
            }
            Write-Host "Found assembly version in .csproj file: " + $version
            return $version
        }
    }
    
    # Fallback to checking AssemblyInfo.cs if no version found in .csproj
    $basePath = "obj\$configuration\net9.0-windows"
    if ($runtime) {
        $basePath = "obj\$configuration\net9.0-windows\$runtime"
    }
    
    $assemblyInfoPath = "$basePath\Windows-Task-Dialog-Generator.AssemblyInfo.cs"
    
    if (Test-Path $assemblyInfoPath) {
        $assemblyFile = Get-Content $assemblyInfoPath
        # Use AssemblyVersionAttribute. Ignore the last version digit if it's zero.
        $versionLine = $assemblyFile | Where-Object { $_ -match 'AssemblyVersionAttribute\("(.*)"\)' } | Select-Object -First 1
        if ($versionLine -match 'AssemblyVersionAttribute\("(\d+\.\d+\.\d+)\.(\d+)"\)') {
            $version = $matches[1]
            if ($matches[2] -ne "0") {
                $version = "$version.$($matches[2])"
            }
            Write-Host "Found assembly version in AssemblyVersionAttribute: " + $version
            return $version
        }
        # Fallback to FileVersion. Ignore the last version digit if it's zero.
        $versionLine = $assemblyFile | Where-Object { $_ -match 'AssemblyFileVersionAttribute\("(.*)"\)' } | Select-Object -First 1
        if ($versionLine -match 'AssemblyFileVersionAttribute\("(\d+\.\d+\.\d+)\.(\d+)"\)') {
            $version = $matches[1]
            if ($matches[2] -ne "0") {
                $version = "$version.$($matches[2])"
            }
            Write-Host "Found assembly version in AssemblyFileVersionAttribute: " + $version
            return $version
        }
        
        # Fall back to AssemblyInformationalVersionAttribute
        $versionLine = $assemblyFile | Where-Object { $_ -match 'AssemblyInformationalVersionAttribute\("(.*)"\)' } | Select-Object -First 1
        if ($versionLine -match 'AssemblyInformationalVersionAttribute\("(.+?)(?:\+|"\))') {
            Write-Host "Found assembly version in AssemblyInformationalVersionAttribute: " + $matches[1]
            return $matches[1]
        }
    }
    else {
        Write-Warning "Couldn't find assembly info file at: $assemblyInfoPath"
        Write-Warning "Couldn't find assembly version. Using default 1.0.0"
        return "1.0.0"
    }
}

# Create results directory
$resultsDir = "bin\Release\Publish-Results"
New-Item -ItemType Directory -Force -Path $resultsDir | Out-Null
Write-Host "Publishing results will be copied to: $($resultsDir)"

$fileNameBase = "Modern-Message-Box-Generator"

# Get all publish profiles
$pubxmlFiles = Get-ChildItem -Path "Properties\PublishProfiles\*.pubxml"

foreach ($pubxmlFile in $pubxmlFiles) {
    Write-Host "Processing publish profile: $($pubxmlFile.Name)"
    
    # Load and parse the pubxml file
    [xml]$pubxml = Get-Content $pubxmlFile.FullName
    $propertyGroup = $pubxml.Project.PropertyGroup
    
    # Extract properties from pubxml
    $publishDir = $propertyGroup.PublishDir
    $runtime = $propertyGroup.RuntimeIdentifier
    $isSelfContained = [System.Convert]::ToBoolean($propertyGroup.SelfContained)
    
    # Determine architecture from runtime
    $architecture = if ($runtime -like "*arm64*") { "ARM64" } else { "x86" }
    
    # Determine type from SelfContained property
    $type = if ($isSelfContained) { "SelfContained" } else { "Framework" }
    
    # Get version for this specific configuration and runtime
    $version = Get-AssemblyVersion -configuration "Release" -runtime $runtime
    
    $assemblyName = "{0}_{1}_{2}-{3}" -f $fileNameBase, $version, $architecture, $type
    
    # Run publish command
    Write-Host "Publishing with runtime: $runtime (Self-contained: $isSelfContained)"
    dotnet publish /p:PublishProfile=$($pubxmlFile.BaseName) /p:AssemblyName=$assemblyName
    
    # Copy the published exe to results directory
    $sourceExe = Join-Path $publishDir "$assemblyName.exe"
    if (Test-Path $sourceExe) {
        Copy-Item $sourceExe -Destination $resultsDir -Force
        Write-Host "Copied $assemblyName.exe to $resultsDir"
    } else {
        Write-Host "Warning: Could not find published exe at $sourceExe"
    }
}

# List all files in the results directory
Write-Host "`nPublished executables in $resultsDir : "
Get-ChildItem $resultsDir -Filter "*.exe" | ForEach-Object {
    Write-Host " - $($_.Name)"
}
# SIG # Begin signature block
# MII97wYJKoZIhvcNAQcCoII94DCCPdwCAQExDzANBglghkgBZQMEAgEFADB5Bgor
# BgEEAYI3AgEEoGswaTA0BgorBgEEAYI3AgEeMCYCAwEAAAQQH8w7YFlLCE63JNLG
# KX7zUQIBAAIBAAIBAAIBAAIBADAxMA0GCWCGSAFlAwQCAQUABCCEFWZ0l1vdQwF1
# y+P7J99doh1iLLk1MvVY7QV/4WY9zqCCIrQwggXMMIIDtKADAgECAhBUmNLR1FsZ
# lUgTecgRwIeZMA0GCSqGSIb3DQEBDAUAMHcxCzAJBgNVBAYTAlVTMR4wHAYDVQQK
# ExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xSDBGBgNVBAMTP01pY3Jvc29mdCBJZGVu
# dGl0eSBWZXJpZmljYXRpb24gUm9vdCBDZXJ0aWZpY2F0ZSBBdXRob3JpdHkgMjAy
# MDAeFw0yMDA0MTYxODM2MTZaFw00NTA0MTYxODQ0NDBaMHcxCzAJBgNVBAYTAlVT
# MR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xSDBGBgNVBAMTP01pY3Jv
# c29mdCBJZGVudGl0eSBWZXJpZmljYXRpb24gUm9vdCBDZXJ0aWZpY2F0ZSBBdXRo
# b3JpdHkgMjAyMDCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIBALORKgeD
# Bmf9np3gx8C3pOZCBH8Ppttf+9Va10Wg+3cL8IDzpm1aTXlT2KCGhFdFIMeiVPvH
# or+Kx24186IVxC9O40qFlkkN/76Z2BT2vCcH7kKbK/ULkgbk/WkTZaiRcvKYhOuD
# PQ7k13ESSCHLDe32R0m3m/nJxxe2hE//uKya13NnSYXjhr03QNAlhtTetcJtYmrV
# qXi8LW9J+eVsFBT9FMfTZRY33stuvF4pjf1imxUs1gXmuYkyM6Nix9fWUmcIxC70
# ViueC4fM7Ke0pqrrBc0ZV6U6CwQnHJFnni1iLS8evtrAIMsEGcoz+4m+mOJyoHI1
# vnnhnINv5G0Xb5DzPQCGdTiO0OBJmrvb0/gwytVXiGhNctO/bX9x2P29Da6SZEi3
# W295JrXNm5UhhNHvDzI9e1eM80UHTHzgXhgONXaLbZ7LNnSrBfjgc10yVpRnlyUK
# xjU9lJfnwUSLgP3B+PR0GeUw9gb7IVc+BhyLaxWGJ0l7gpPKWeh1R+g/OPTHU3mg
# trTiXFHvvV84wRPmeAyVWi7FQFkozA8kwOy6CXcjmTimthzax7ogttc32H83rwjj
# O3HbbnMbfZlysOSGM1l0tRYAe1BtxoYT2v3EOYI9JACaYNq6lMAFUSw0rFCZE4e7
# swWAsk0wAly4JoNdtGNz764jlU9gKL431VulAgMBAAGjVDBSMA4GA1UdDwEB/wQE
# AwIBhjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBTIftJqhSobyhmYBAcnz1AQ
# T2ioojAQBgkrBgEEAYI3FQEEAwIBADANBgkqhkiG9w0BAQwFAAOCAgEAr2rd5hnn
# LZRDGU7L6VCVZKUDkQKL4jaAOxWiUsIWGbZqWl10QzD0m/9gdAmxIR6QFm3FJI9c
# Zohj9E/MffISTEAQiwGf2qnIrvKVG8+dBetJPnSgaFvlVixlHIJ+U9pW2UYXeZJF
# xBA2CFIpF8svpvJ+1Gkkih6PsHMNzBxKq7Kq7aeRYwFkIqgyuH4yKLNncy2RtNwx
# AQv3Rwqm8ddK7VZgxCwIo3tAsLx0J1KH1r6I3TeKiW5niB31yV2g/rarOoDXGpc8
# FzYiQR6sTdWD5jw4vU8w6VSp07YEwzJ2YbuwGMUrGLPAgNW3lbBeUU0i/OxYqujY
# lLSlLu2S3ucYfCFX3VVj979tzR/SpncocMfiWzpbCNJbTsgAlrPhgzavhgplXHT2
# 6ux6anSg8Evu75SjrFDyh+3XOjCDyft9V77l4/hByuVkrrOj7FjshZrM77nq81YY
# uVxzmq/FdxeDWds3GhhyVKVB0rYjdaNDmuV3fJZ5t0GNv+zcgKCf0Xd1WF81E+Al
# GmcLfc4l+gcK5GEh2NQc5QfGNpn0ltDGFf5Ozdeui53bFv0ExpK91IjmqaOqu/dk
# ODtfzAzQNb50GQOmxapMomE2gj4d8yu8l13bS3g7LfU772Aj6PXsCyM2la+YZr9T
# 03u4aUoqlmZpxJTG9F9urJh4iIAGXKKy7aIwggbuMIIE1qADAgECAhMzAAK5B7Gc
# zjpXwC3oAAAAArkHMA0GCSqGSIb3DQEBDAUAMFoxCzAJBgNVBAYTAlVTMR4wHAYD
# VQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xKzApBgNVBAMTIk1pY3Jvc29mdCBJ
# RCBWZXJpZmllZCBDUyBBT0MgQ0EgMDIwHhcNMjUwMjExMTI1OTQyWhcNMjUwMjE0
# MTI1OTQyWjBsMQswCQYDVQQGEwJVUzEQMA4GA1UECBMHV3lvbWluZzERMA8GA1UE
# BxMIU2hlcmlkYW4xGzAZBgNVBAoTElRoaW8gU29mdHdhcmUsIExMQzEbMBkGA1UE
# AxMSVGhpbyBTb2Z0d2FyZSwgTExDMIIBojANBgkqhkiG9w0BAQEFAAOCAY8AMIIB
# igKCAYEAm23nXSBBFQHK8UGnh/r3CLxpKuUMuCfQQN+Hs4BBStQO4NA0MsDCmhtG
# JKsyxgEyK0+rrQFFPEmg8/f6J76vFm6PSY/Pp+9ZiMux32b5HOQZn4P/XtrrAvVS
# LjPLdvSmpA/Jkxx1JB6lDFX46cIYGWtoQQQq8acmMo5Zc8srf4B389OHtZk30xVk
# vhdXsXaspdj5hV6MhyB0Hxwtvjoy7TNLZS5JScxRzO8i6iSJsCmuIxh0j8EPkuBr
# dkrNDDfCsiZDi5VETweknOpMFcEu59JCoXeTivSS4oeooTwuXjq/CALaL2TuK5sw
# jz26yPv/1iJ51EuYmLxdr6HBpJSMacD0SU7obCsL9Mc805Yl9AktQVzxXQVOoj9G
# 1tcQgrb8P/ShknR1u58gV0dkdcw48loT0h41a9l/LaEvD/24wLgEd6o6FcjR18IS
# fvLLzrarS9aiNb/2ECvYtL6+fBGFs9F02ETkNc6u6wJ2ecQlGCKTsSePeR/4K2oY
# GbmfEA/vAgMBAAGjggIZMIICFTAMBgNVHRMBAf8EAjAAMA4GA1UdDwEB/wQEAwIH
# gDA8BgNVHSUENTAzBgorBgEEAYI3YQEABggrBgEFBQcDAwYbKwYBBAGCN2GCyITf
# TKbD3mqByam9GIO77qlmMB0GA1UdDgQWBBQC9+Il1MGyD4UxdvPXYxBk/xOcuzAf
# BgNVHSMEGDAWgBQkRZmhd5AqfMPKg7BuZBaEKvgsZzBnBgNVHR8EYDBeMFygWqBY
# hlZodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpb3BzL2NybC9NaWNyb3NvZnQl
# MjBJRCUyMFZlcmlmaWVkJTIwQ1MlMjBBT0MlMjBDQSUyMDAyLmNybDCBpQYIKwYB
# BQUHAQEEgZgwgZUwZAYIKwYBBQUHMAKGWGh0dHA6Ly93d3cubWljcm9zb2Z0LmNv
# bS9wa2lvcHMvY2VydHMvTWljcm9zb2Z0JTIwSUQlMjBWZXJpZmllZCUyMENTJTIw
# QU9DJTIwQ0ElMjAwMi5jcnQwLQYIKwYBBQUHMAGGIWh0dHA6Ly9vbmVvY3NwLm1p
# Y3Jvc29mdC5jb20vb2NzcDBmBgNVHSAEXzBdMFEGDCsGAQQBgjdMg30BATBBMD8G
# CCsGAQUFBwIBFjNodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpb3BzL0RvY3Mv
# UmVwb3NpdG9yeS5odG0wCAYGZ4EMAQQBMA0GCSqGSIb3DQEBDAUAA4ICAQBdnNI6
# CPeZEMPrA1N/zzo16ZvcwKpchue7YwvT3ZhNBo953DCxVK5TbiQyPeDa5FneGxsd
# +POkdEPUfddW2ALKUnJ/mM8InHiUmdHcDtfrnGcuLjETnxfM9klO2EslFgFawCI+
# M16foCVcYoGOeoSaKQptugMM+RW09Y1evdjy/qLcGv579xYkYrUmSyNcQ8DeeYzW
# SZnIlsISPUf8ksJjAzbCAd6snKglnf9BleyeTUfB+4D8AskLbZHuQCKT5UnqWgvJ
# KuXYE7MMSnalEGRUMZcNeeLV9RulZrGlyhC1xVo4t5n0MMfPHU+uquhtdOHdVZFk
# dLi962STmX5UGxU13szwHsDz5OsEwUGctH+w7+tPapbhu4lh4I6n1urY3bUChSEZ
# evKuai2mRIbh1TJ23/BXc7Nnar3N2uTiLjUJ02/LWJGyOvrlrTU2iqjV/JgCndLN
# dTAWR8rGaOdT4GHF4Jrhiy6LFwQrCJ0+6Le3xkF1R4AMMM/FBHr0w8D5XnN/0M1f
# 6VneOrPHXWcM9IzvGq8GdLVRfHGsvyD2EDfYfuVAIthXDQ6aU1Df+ILzYBsBzYZ3
# GEDOK1jEKVTYNBNWeu+q6VUDDryUawMjXUQmyYQINGjkKrFAMknBxK0sFg1gQtMs
# /+A+4inUkO61107dMKou+TNOrxXb9BlW+ti9IzCCBu4wggTWoAMCAQICEzMAArkH
# sZzOOlfALegAAAACuQcwDQYJKoZIhvcNAQEMBQAwWjELMAkGA1UEBhMCVVMxHjAc
# BgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjErMCkGA1UEAxMiTWljcm9zb2Z0
# IElEIFZlcmlmaWVkIENTIEFPQyBDQSAwMjAeFw0yNTAyMTExMjU5NDJaFw0yNTAy
# MTQxMjU5NDJaMGwxCzAJBgNVBAYTAlVTMRAwDgYDVQQIEwdXeW9taW5nMREwDwYD
# VQQHEwhTaGVyaWRhbjEbMBkGA1UEChMSVGhpbyBTb2Z0d2FyZSwgTExDMRswGQYD
# VQQDExJUaGlvIFNvZnR3YXJlLCBMTEMwggGiMA0GCSqGSIb3DQEBAQUAA4IBjwAw
# ggGKAoIBgQCbbeddIEEVAcrxQaeH+vcIvGkq5Qy4J9BA34ezgEFK1A7g0DQywMKa
# G0YkqzLGATIrT6utAUU8SaDz9/onvq8Wbo9Jj8+n71mIy7HfZvkc5Bmfg/9e2usC
# 9VIuM8t29KakD8mTHHUkHqUMVfjpwhgZa2hBBCrxpyYyjllzyyt/gHfz04e1mTfT
# FWS+F1exdqyl2PmFXoyHIHQfHC2+OjLtM0tlLklJzFHM7yLqJImwKa4jGHSPwQ+S
# 4Gt2Ss0MN8KyJkOLlURPB6Sc6kwVwS7n0kKhd5OK9JLih6ihPC5eOr8IAtovZO4r
# mzCPPbrI+//WInnUS5iYvF2vocGklIxpwPRJTuhsKwv0xzzTliX0CS1BXPFdBU6i
# P0bW1xCCtvw/9KGSdHW7nyBXR2R1zDjyWhPSHjVr2X8toS8P/bjAuAR3qjoVyNHX
# whJ+8svOtqtL1qI1v/YQK9i0vr58EYWz0XTYROQ1zq7rAnZ5xCUYIpOxJ495H/gr
# ahgZuZ8QD+8CAwEAAaOCAhkwggIVMAwGA1UdEwEB/wQCMAAwDgYDVR0PAQH/BAQD
# AgeAMDwGA1UdJQQ1MDMGCisGAQQBgjdhAQAGCCsGAQUFBwMDBhsrBgEEAYI3YYLI
# hN9MpsPeaoHJqb0Yg7vuqWYwHQYDVR0OBBYEFAL34iXUwbIPhTF289djEGT/E5y7
# MB8GA1UdIwQYMBaAFCRFmaF3kCp8w8qDsG5kFoQq+CxnMGcGA1UdHwRgMF4wXKBa
# oFiGVmh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY3JsL01pY3Jvc29m
# dCUyMElEJTIwVmVyaWZpZWQlMjBDUyUyMEFPQyUyMENBJTIwMDIuY3JsMIGlBggr
# BgEFBQcBAQSBmDCBlTBkBggrBgEFBQcwAoZYaHR0cDovL3d3dy5taWNyb3NvZnQu
# Y29tL3BraW9wcy9jZXJ0cy9NaWNyb3NvZnQlMjBJRCUyMFZlcmlmaWVkJTIwQ1Ml
# MjBBT0MlMjBDQSUyMDAyLmNydDAtBggrBgEFBQcwAYYhaHR0cDovL29uZW9jc3Au
# bWljcm9zb2Z0LmNvbS9vY3NwMGYGA1UdIARfMF0wUQYMKwYBBAGCN0yDfQEBMEEw
# PwYIKwYBBQUHAgEWM2h0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvRG9j
# cy9SZXBvc2l0b3J5Lmh0bTAIBgZngQwBBAEwDQYJKoZIhvcNAQEMBQADggIBAF2c
# 0joI95kQw+sDU3/POjXpm9zAqlyG57tjC9PdmE0Gj3ncMLFUrlNuJDI94NrkWd4b
# Gx3486R0Q9R911bYAspScn+YzwiceJSZ0dwO1+ucZy4uMROfF8z2SU7YSyUWAVrA
# Ij4zXp+gJVxigY56hJopCm26Awz5FbT1jV692PL+otwa/nv3FiRitSZLI1xDwN55
# jNZJmciWwhI9R/ySwmMDNsIB3qycqCWd/0GV7J5NR8H7gPwCyQttke5AIpPlSepa
# C8kq5dgTswxKdqUQZFQxlw154tX1G6VmsaXKELXFWji3mfQwx88dT66q6G104d1V
# kWR0uL3rZJOZflQbFTXezPAewPPk6wTBQZy0f7Dv609qluG7iWHgjqfW6tjdtQKF
# IRl68q5qLaZEhuHVMnbf8Fdzs2dqvc3a5OIuNQnTb8tYkbI6+uWtNTaKqNX8mAKd
# 0s11MBZHysZo51PgYcXgmuGLLosXBCsInT7ot7fGQXVHgAwwz8UEevTDwPlec3/Q
# zV/pWd46s8ddZwz0jO8arwZ0tVF8cay/IPYQN9h+5UAi2FcNDppTUN/4gvNgGwHN
# hncYQM4rWMQpVNg0E1Z676rpVQMOvJRrAyNdRCbJhAg0aOQqsUAyScHErSwWDWBC
# 0yz/4D7iKdSQ7rXXTt0wqi75M06vFdv0GVb62L0jMIIHWjCCBUKgAwIBAgITMwAA
# AASWUEvS2+7LiAAAAAAABDANBgkqhkiG9w0BAQwFADBjMQswCQYDVQQGEwJVUzEe
# MBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMTQwMgYDVQQDEytNaWNyb3Nv
# ZnQgSUQgVmVyaWZpZWQgQ29kZSBTaWduaW5nIFBDQSAyMDIxMB4XDTIxMDQxMzE3
# MzE1MloXDTI2MDQxMzE3MzE1MlowWjELMAkGA1UEBhMCVVMxHjAcBgNVBAoTFU1p
# Y3Jvc29mdCBDb3Jwb3JhdGlvbjErMCkGA1UEAxMiTWljcm9zb2Z0IElEIFZlcmlm
# aWVkIENTIEFPQyBDQSAwMjCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoCggIB
# AOHOoOgzomOmwDsAj2wZUBdrY6N3JFGbmm+WaKzJ0aeKzpsGQ4k2yKcxZGf5PJOI
# rwSVdcOf2/6MpCPnlwKmmsTHcgDtDKHZxFuyJ30Pq05MpBMx8UWwjYOig7E52HP2
# HS+yCIiZYvJOdbqWhyy+wmJvWDXNEhWL5WhY9jtB4zvcvzUZnFjY2pmTpUY8VtnF
# oFLFHWs0h4EQnpPO1dmzP9e2/qPFl1FvdSKYIEWrJomeuVhBR1ym8oZti24QSumV
# pkKBXhPhlqylghiv6v+EYk2jDYR11r1r/v/yOfFLTsVYtw2itX0OmC8iCBh8w+Ap
# rXKxor8bqav3K6x7pxjQe//0JrpdmT/R3DpmP2qbYFJ8E/ttIPwN+4g37rlcOskt
# i6NP5Kf42/ifLxOBTKiIsMRgci+PNjzFQQt6nfzWxUGvDJo+np7FPhxKr/Wq/gG3
# CsLpm2aiSSpkKxmkjXVn5NjaHYHFjpqu48oW8cGTo5y49P28J7FDXDQHtPb/qoqM
# 8kEHrPAN1Fz3EUG/BvnNMmjtiAon1kyu8krslCfPJNZrTdtgjX7W44rYgHmn6GfV
# ZoZ+UX2/kvyuWq1b03C7pLeT3Uw0MZeeexCBOgPulxQaXbIzs5C83RIexC5PD1Tz
# I0HzwoCrSfOHNe33dgvfqcRdZREFBV2P2LQi/jZrPXFlAgMBAAGjggIOMIICCjAO
# BgNVHQ8BAf8EBAMCAYYwEAYJKwYBBAGCNxUBBAMCAQAwHQYDVR0OBBYEFCRFmaF3
# kCp8w8qDsG5kFoQq+CxnMFQGA1UdIARNMEswSQYEVR0gADBBMD8GCCsGAQUFBwIB
# FjNodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpb3BzL0RvY3MvUmVwb3NpdG9y
# eS5odG0wGQYJKwYBBAGCNxQCBAweCgBTAHUAYgBDAEEwEgYDVR0TAQH/BAgwBgEB
# /wIBADAfBgNVHSMEGDAWgBTZQSmwDw9jbO9p1/XNKZ6kSGow5jBwBgNVHR8EaTBn
# MGWgY6Bhhl9odHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpb3BzL2NybC9NaWNy
# b3NvZnQlMjBJRCUyMFZlcmlmaWVkJTIwQ29kZSUyMFNpZ25pbmclMjBQQ0ElMjAy
# MDIxLmNybDCBrgYIKwYBBQUHAQEEgaEwgZ4wbQYIKwYBBQUHMAKGYWh0dHA6Ly93
# d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY2VydHMvTWljcm9zb2Z0JTIwSUQlMjBW
# ZXJpZmllZCUyMENvZGUlMjBTaWduaW5nJTIwUENBJTIwMjAyMS5jcnQwLQYIKwYB
# BQUHMAGGIWh0dHA6Ly9vbmVvY3NwLm1pY3Jvc29mdC5jb20vb2NzcDANBgkqhkiG
# 9w0BAQwFAAOCAgEAZy04XZWzDSKJHSrc0mvIqPqRDveQnN1TsmP4ULCCHHTMpNoS
# Tsy7fzNVl30MhJQ5P0Lci81+t03Tm+SfpzvLdKc88Iu2WLzIjairwEDudLDDiZ90
# 94Qj6acTTYaBhVcc9lMokOG9rzq3LCyvUzhBV1m1DCTm0fTzNMGbAASIbuJOlVS8
# RA3tBknkF/2ROzx304OOC7n7eCCqmJp79QrqLKd4JRWLFXoC5zFmVGfFLTvRfEAo
# gKLiWIS+TpQpLIA2/b3vx0ISxZ3pX4OnULmyBbKgfSJQqJ2CiWfx2jGb2LQO8vRD
# kSuHMZb03rQlwB2soklx9LnhP0/dsFRtHLL+VXVMo+sla5ttr5SmAJFyDSrwzgfP
# rOIfk4EoZVGtgArthVp+yc5U0m6ZNCBPERLmJpLshPwU5JPd1gzMez8C55+CfuX5
# L2440NPDnsH6TIYfErj3UCqpmeNCOFtlMiSjDE23rdeiRYpkqgwoYJwgepcJaXtI
# H26Pe1O6a6W3wSqegdpNn+2Pk41q0GDfjnXDzskAHcRhjwcCUmiRt6IXZJQsYACe
# WpwsXmJe0o0ORLmumrYyHlYTdCnzyxT6WM+QkFPiQth+/ceHfzumDhUfWmHuePwh
# rqe3UVCHy0r9f49Az3OhJX92MlsZaFo/MnmN5B62RWgJUTMIQF8j0N6xF/cwggee
# MIIFhqADAgECAhMzAAAAB4ejNKN7pY4cAAAAAAAHMA0GCSqGSIb3DQEBDAUAMHcx
# CzAJBgNVBAYTAlVTMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9yYXRpb24xSDBG
# BgNVBAMTP01pY3Jvc29mdCBJZGVudGl0eSBWZXJpZmljYXRpb24gUm9vdCBDZXJ0
# aWZpY2F0ZSBBdXRob3JpdHkgMjAyMDAeFw0yMTA0MDEyMDA1MjBaFw0zNjA0MDEy
# MDE1MjBaMGMxCzAJBgNVBAYTAlVTMR4wHAYDVQQKExVNaWNyb3NvZnQgQ29ycG9y
# YXRpb24xNDAyBgNVBAMTK01pY3Jvc29mdCBJRCBWZXJpZmllZCBDb2RlIFNpZ25p
# bmcgUENBIDIwMjEwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCy8MCv
# GYgo4t1UekxJbGkIVQm0Uv96SvjB6yUo92cXdylN65Xy96q2YpWCiTas7QPTkGnK
# 9QMKDXB2ygS27EAIQZyAd+M8X+dmw6SDtzSZXyGkxP8a8Hi6EO9Zcwh5A+wOALNQ
# bNO+iLvpgOnEM7GGB/wm5dYnMEOguua1OFfTUITVMIK8faxkP/4fPdEPCXYyy8NJ
# 1fmskNhW5HduNqPZB/NkWbB9xxMqowAeWvPgHtpzyD3PLGVOmRO4ka0WcsEZqyg6
# efk3JiV/TEX39uNVGjgbODZhzspHvKFNU2K5MYfmHh4H1qObU4JKEjKGsqqA6Rzi
# ybPqhvE74fEp4n1tiY9/ootdU0vPxRp4BGjQFq28nzawuvaCqUUF2PWxh+o5/TRC
# b/cHhcYU8Mr8fTiS15kRmwFFzdVPZ3+JV3s5MulIf3II5FXeghlAH9CvicPhhP+V
# aSFW3Da/azROdEm5sv+EUwhBrzqtxoYyE2wmuHKws00x4GGIx7NTWznOm6x/niqV
# i7a/mxnnMvQq8EMse0vwX2CfqM7Le/smbRtsEeOtbnJBbtLfoAsC3TdAOnBbUkbU
# fG78VRclsE7YDDBUbgWt75lDk53yi7C3n0WkHFU4EZ83i83abd9nHWCqfnYa9qIH
# PqjOiuAgSOf4+FRcguEBXlD9mAInS7b6V0UaNwIDAQABo4ICNTCCAjEwDgYDVR0P
# AQH/BAQDAgGGMBAGCSsGAQQBgjcVAQQDAgEAMB0GA1UdDgQWBBTZQSmwDw9jbO9p
# 1/XNKZ6kSGow5jBUBgNVHSAETTBLMEkGBFUdIAAwQTA/BggrBgEFBQcCARYzaHR0
# cDovL3d3dy5taWNyb3NvZnQuY29tL3BraW9wcy9Eb2NzL1JlcG9zaXRvcnkuaHRt
# MBkGCSsGAQQBgjcUAgQMHgoAUwB1AGIAQwBBMA8GA1UdEwEB/wQFMAMBAf8wHwYD
# VR0jBBgwFoAUyH7SaoUqG8oZmAQHJ89QEE9oqKIwgYQGA1UdHwR9MHsweaB3oHWG
# c2h0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY3JsL01pY3Jvc29mdCUy
# MElkZW50aXR5JTIwVmVyaWZpY2F0aW9uJTIwUm9vdCUyMENlcnRpZmljYXRlJTIw
# QXV0aG9yaXR5JTIwMjAyMC5jcmwwgcMGCCsGAQUFBwEBBIG2MIGzMIGBBggrBgEF
# BQcwAoZ1aHR0cDovL3d3dy5taWNyb3NvZnQuY29tL3BraW9wcy9jZXJ0cy9NaWNy
# b3NvZnQlMjBJZGVudGl0eSUyMFZlcmlmaWNhdGlvbiUyMFJvb3QlMjBDZXJ0aWZp
# Y2F0ZSUyMEF1dGhvcml0eSUyMDIwMjAuY3J0MC0GCCsGAQUFBzABhiFodHRwOi8v
# b25lb2NzcC5taWNyb3NvZnQuY29tL29jc3AwDQYJKoZIhvcNAQEMBQADggIBAH8l
# Kp7+1Kvq3WYK21cjTLpebJDjW4ZbOX3HD5ZiG84vjsFXT0OB+eb+1TiJ55ns0BHl
# uC6itMI2vnwc5wDW1ywdCq3TAmx0KWy7xulAP179qX6VSBNQkRXzReFyjvF2BGt6
# FvKFR/imR4CEESMAG8hSkPYso+GjlngM8JPn/ROUrTaeU/BRu/1RFESFVgK2wMz7
# fU4VTd8NXwGZBe/mFPZG6tWwkdmA/jLbp0kNUX7elxu2+HtHo0QO5gdiKF+YTYd1
# BGrmNG8sTURvn09jAhIUJfYNotn7OlThtfQjXqe0qrimgY4Vpoq2MgDW9ESUi1o4
# pzC1zTgIGtdJ/IvY6nqa80jFOTg5qzAiRNdsUvzVkoYP7bi4wLCj+ks2GftUct+f
# GUxXMdBUv5sdr0qFPLPB0b8vq516slCfRwaktAxK1S40MCvFbbAXXpAZnU20FaAo
# Dwqq/jwzwd8Wo2J83r7O3onQbDO9TyDStgaBNlHzMMQgl95nHBYMelLEHkUnVVVT
# UsgC0Huj09duNfMaJ9ogxhPNThgq3i8w3DAGZ61AMeF0C1M+mU5eucj1Ijod5O2M
# MPeJQ3/vKBtqGZg4eTtUHt/BPjN74SsJsyHqAdXVS5c+ItyKWg3Eforhox9k3Wgt
# WTpgV4gkSiS4+A09roSdOI4vrRw+p+fL4WrxSK5nMYIakTCCGo0CAQEwcTBaMQsw
# CQYDVQQGEwJVUzEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9uMSswKQYD
# VQQDEyJNaWNyb3NvZnQgSUQgVmVyaWZpZWQgQ1MgQU9DIENBIDAyAhMzAAK5B7Gc
# zjpXwC3oAAAAArkHMA0GCWCGSAFlAwQCAQUAoF4wEAYKKwYBBAGCNwIBDDECMAAw
# GQYJKoZIhvcNAQkDMQwGCisGAQQBgjcCAQQwLwYJKoZIhvcNAQkEMSIEIB+FMDfc
# GlYwD9E/URJ9ZnrgkPsncO/0hkxfx882/aiFMA0GCSqGSIb3DQEBAQUABIIBgFX0
# st+UFuRnIr5SbmLFlDWZNmsimzm5PiD/PzoR3aBJAz74whRwh50g3alSm3Aoum4h
# d0x9b5alkTWpFZceCJbAlgJnae/CfIu7WW/O5Ltzl3JiIBwXe8g7CLoLuCXDO1Ta
# L+siAN9la1BYAg4kYNJHxluqViVwaXlANEgEFynOGytw3VZB0dD70JHHi/j7CYaW
# 7Y1uk7kUJpuim0YVEqY3EOtwdSXy7P16fF6OIruKM6mr3oBsDpWSg9CxuVjm0J/s
# PTbopYbJBwkM/ag9FTGDzpbezQiSbfvlDnTbE6R11Ldqqor5RMW18MdEZYrsXAYi
# iJHmJUQsVuvXYmzkjNbqFyXNczEbEf3AD+rsqDc7kjFbi4pGzqp54a9mPT0lD88M
# KefEukuIyNGRSVe0XnUoXfGWZuEZTGpQw6slnp95vQTbIE/gSh6ZB/lJwvbCskQJ
# 8DiaHhmXBVT/njCIMg8FY/u7HRFbBUz8HCkU46ha4s4FBkLIms0HXL18BBCwTqGC
# GBEwghgNBgorBgEEAYI3AwMBMYIX/TCCF/kGCSqGSIb3DQEHAqCCF+owghfmAgED
# MQ8wDQYJYIZIAWUDBAIBBQAwggFiBgsqhkiG9w0BCRABBKCCAVEEggFNMIIBSQIB
# AQYKKwYBBAGEWQoDATAxMA0GCWCGSAFlAwQCAQUABCBULmmQ1AbRwprL7klRk4a5
# 535siOHPy/qsPWsIioSi5QIGZ5dsB5/8GBMyMDI1MDIxMTE5MTI0Mi40NzRaMASA
# AgH0oIHhpIHeMIHbMQswCQYDVQQGEwJVUzETMBEGA1UECBMKV2FzaGluZ3RvbjEQ
# MA4GA1UEBxMHUmVkbW9uZDEeMBwGA1UEChMVTWljcm9zb2Z0IENvcnBvcmF0aW9u
# MSUwIwYDVQQLExxNaWNyb3NvZnQgQW1lcmljYSBPcGVyYXRpb25zMScwJQYDVQQL
# Ex5uU2hpZWxkIFRTUyBFU046N0QwMC0wNUUwLUQ5NDcxNTAzBgNVBAMTLE1pY3Jv
# c29mdCBQdWJsaWMgUlNBIFRpbWUgU3RhbXBpbmcgQXV0aG9yaXR5oIIPITCCB4Iw
# ggVqoAMCAQICEzMAAAAF5c8P/2YuyYcAAAAAAAUwDQYJKoZIhvcNAQEMBQAwdzEL
# MAkGA1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjFIMEYG
# A1UEAxM/TWljcm9zb2Z0IElkZW50aXR5IFZlcmlmaWNhdGlvbiBSb290IENlcnRp
# ZmljYXRlIEF1dGhvcml0eSAyMDIwMB4XDTIwMTExOTIwMzIzMVoXDTM1MTExOTIw
# NDIzMVowYTELMAkGA1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3Jh
# dGlvbjEyMDAGA1UEAxMpTWljcm9zb2Z0IFB1YmxpYyBSU0EgVGltZXN0YW1waW5n
# IENBIDIwMjAwggIiMA0GCSqGSIb3DQEBAQUAA4ICDwAwggIKAoICAQCefOdSY/3g
# xZ8FfWO1BiKjHB7X55cz0RMFvWVGR3eRwV1wb3+yq0OXDEqhUhxqoNv6iYWKjkMc
# LhEFxvJAeNcLAyT+XdM5i2CgGPGcb95WJLiw7HzLiBKrxmDj1EQB/mG5eEiRBEp7
# dDGzxKCnTYocDOcRr9KxqHydajmEkzXHOeRGwU+7qt8Md5l4bVZrXAhK+WSk5Cih
# NQsWbzT1nRliVDwunuLkX1hyIWXIArCfrKM3+RHh+Sq5RZ8aYyik2r8HxT+l2hmR
# llBvE2Wok6IEaAJanHr24qoqFM9WLeBUSudz+qL51HwDYyIDPSQ3SeHtKog0ZubD
# k4hELQSxnfVYXdTGncaBnB60QrEuazvcob9n4yR65pUNBCF5qeA4QwYnilBkfnme
# AjRN3LVuLr0g0FXkqfYdUmj1fFFhH8k8YBozrEaXnsSL3kdTD01X+4LfIWOuFzTz
# uoslBrBILfHNj8RfOxPgjuwNvE6YzauXi4orp4Sm6tF245DaFOSYbWFK5ZgG6cUY
# 2/bUq3g3bQAqZt65KcaewEJ3ZyNEobv35Nf6xN6FrA6jF9447+NHvCjeWLCQZ3M8
# lgeCcnnhTFtyQX3XgCoc6IRXvFOcPVrr3D9RPHCMS6Ckg8wggTrtIVnY8yjbvGOU
# sAdZbeXUIQAWMs0d3cRDv09SvwVRd61evQIDAQABo4ICGzCCAhcwDgYDVR0PAQH/
# BAQDAgGGMBAGCSsGAQQBgjcVAQQDAgEAMB0GA1UdDgQWBBRraSg6NS9IY0DPe9iv
# Sek+2T3bITBUBgNVHSAETTBLMEkGBFUdIAAwQTA/BggrBgEFBQcCARYzaHR0cDov
# L3d3dy5taWNyb3NvZnQuY29tL3BraW9wcy9Eb2NzL1JlcG9zaXRvcnkuaHRtMBMG
# A1UdJQQMMAoGCCsGAQUFBwMIMBkGCSsGAQQBgjcUAgQMHgoAUwB1AGIAQwBBMA8G
# A1UdEwEB/wQFMAMBAf8wHwYDVR0jBBgwFoAUyH7SaoUqG8oZmAQHJ89QEE9oqKIw
# gYQGA1UdHwR9MHsweaB3oHWGc2h0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lv
# cHMvY3JsL01pY3Jvc29mdCUyMElkZW50aXR5JTIwVmVyaWZpY2F0aW9uJTIwUm9v
# dCUyMENlcnRpZmljYXRlJTIwQXV0aG9yaXR5JTIwMjAyMC5jcmwwgZQGCCsGAQUF
# BwEBBIGHMIGEMIGBBggrBgEFBQcwAoZ1aHR0cDovL3d3dy5taWNyb3NvZnQuY29t
# L3BraW9wcy9jZXJ0cy9NaWNyb3NvZnQlMjBJZGVudGl0eSUyMFZlcmlmaWNhdGlv
# biUyMFJvb3QlMjBDZXJ0aWZpY2F0ZSUyMEF1dGhvcml0eSUyMDIwMjAuY3J0MA0G
# CSqGSIb3DQEBDAUAA4ICAQBfiHbHfm21WhV150x4aPpO4dhEmSUVpbixNDmv6Tvu
# IHv1xIs174bNGO/ilWMm+Jx5boAXrJxagRhHQtiFprSjMktTliL4sKZyt2i+SXnc
# M23gRezzsoOiBhv14YSd1Klnlkzvgs29XNjT+c8hIfPRe9rvVCMPiH7zPZcw5nNj
# thDQ+zD563I1nUJ6y59TbXWsuyUsqw7wXZoGzZwijWT5oc6GvD3HDokJY401uhnj
# 3ubBhbkR83RbfMvmzdp3he2bvIUztSOuFzRqrLfEvsPkVHYnvH1wtYyrt5vShiKh
# eGpXa2AWpsod4OJyT4/y0dggWi8g/tgbhmQlZqDUf3UqUQsZaLdIu/XSjgoZqDja
# mzCPJtOLi2hBwL+KsCh0Nbwc21f5xvPSwym0Ukr4o5sCcMUcSy6TEP7uMV8RX0eH
# /4JLEpGyae6Ki8JYg5v4fsNGif1OXHJ2IWG+7zyjTDfkmQ1snFOTgyEX8qBpefQb
# F0fx6URrYiarjmBprwP6ZObwtZXJ23jK3Fg/9uqM3j0P01nzVygTppBabzxPAh/h
# Hhhls6kwo3QLJ6No803jUsZcd4JQxiYHHc+Q/wAMcPUnYKv/q2O444LO1+n6j01z
# 5mggCSlRwD9faBIySAcA9S8h22hIAcRQqIGEjolCK9F6nK9ZyX4lhthsGHumaABd
# WzCCB5cwggV/oAMCAQICEzMAAABLobGt4Vn85zQAAAAAAEswDQYJKoZIhvcNAQEM
# BQAwYTELMAkGA1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlv
# bjEyMDAGA1UEAxMpTWljcm9zb2Z0IFB1YmxpYyBSU0EgVGltZXN0YW1waW5nIENB
# IDIwMjAwHhcNMjQxMTI2MTg0ODU3WhcNMjUxMTE5MTg0ODU3WjCB2zELMAkGA1UE
# BhMCVVMxEzARBgNVBAgTCldhc2hpbmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAc
# BgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjElMCMGA1UECxMcTWljcm9zb2Z0
# IEFtZXJpY2EgT3BlcmF0aW9uczEnMCUGA1UECxMeblNoaWVsZCBUU1MgRVNOOjdE
# MDAtMDVFMC1EOTQ3MTUwMwYDVQQDEyxNaWNyb3NvZnQgUHVibGljIFJTQSBUaW1l
# IFN0YW1waW5nIEF1dGhvcml0eTCCAiIwDQYJKoZIhvcNAQEBBQADggIPADCCAgoC
# ggIBAJ2dirN/NIMtny38hycGFn9VLvt/PswhQprUj2YOOclE091Vai+aBTlRsBEJ
# ssIgjNmPwnT9gN7IkENgVPJJcCBoeUPDTqtQFyvKrZ5rGhZ9KFMdJ2U6fLOENTDw
# ZcZglPXH+r6cabqTWiu7BbbCtg1Hzr9DmyvVdgImUzzK15ZokW9kkYTq8I49DGeL
# +UQ3aqhOurZ6OalVUw+eCRf0gwLKuXFq/jSALXlZNTt1nejX1tCzu752vNvM43Qy
# 0qyprW8MWwe6q8farVLbXMROZ53+WWZMrlBpEsuGTlYJ33DWf8OjmAdquDom/zrW
# 5IKoB0x02cjfh+dOwhGdoS0IZYa7tbVl3tuUdKWKAFoYAsgLrW8nNaPUxvwnGGGa
# F89fbR3qcHUmmabiog/8VbTa4LElKr0V7zOJ52+WDibVoKqNZfRDnrr+LtWJ5Ww4
# DevHXFFd4hsAOazGfDfpiVmiGypESxlQyNBnh7pwJ8oCVo7TZxrsaLMhGfuY2/Mc
# 1hzjuBAIUQL5iBfZIu/DhvpHlNqrjdcnSF+EPA9I+JPrR3JKMtQhyYNyza8jzvy3
# dbESXZqf0ckJpg8q9X9RnUDL0eORIlzdmohe+AaWHVUjuQKk9MFrJjtELQjMmXlr
# v4MzsVwGF6L2HV4nwB1mzNVxQaT4uQX66pTcYCeNhp0kL/HZAgMBAAGjggHLMIIB
# xzAdBgNVHQ4EFgQUIJkaxS9FUX/NOhFaQTclhaa4dCYwHwYDVR0jBBgwFoAUa2ko
# OjUvSGNAz3vYr0npPtk92yEwbAYDVR0fBGUwYzBhoF+gXYZbaHR0cDovL3d3dy5t
# aWNyb3NvZnQuY29tL3BraW9wcy9jcmwvTWljcm9zb2Z0JTIwUHVibGljJTIwUlNB
# JTIwVGltZXN0YW1waW5nJTIwQ0ElMjAyMDIwLmNybDB5BggrBgEFBQcBAQRtMGsw
# aQYIKwYBBQUHMAKGXWh0dHA6Ly93d3cubWljcm9zb2Z0LmNvbS9wa2lvcHMvY2Vy
# dHMvTWljcm9zb2Z0JTIwUHVibGljJTIwUlNBJTIwVGltZXN0YW1waW5nJTIwQ0El
# MjAyMDIwLmNydDAMBgNVHRMBAf8EAjAAMBYGA1UdJQEB/wQMMAoGCCsGAQUFBwMI
# MA4GA1UdDwEB/wQEAwIHgDBmBgNVHSAEXzBdMFEGDCsGAQQBgjdMg30BATBBMD8G
# CCsGAQUFBwIBFjNodHRwOi8vd3d3Lm1pY3Jvc29mdC5jb20vcGtpb3BzL0RvY3Mv
# UmVwb3NpdG9yeS5odG0wCAYGZ4EMAQQCMA0GCSqGSIb3DQEBDAUAA4ICAQAxvdhs
# 2DI5Qh2+uaHzIrblBbNTiRVS+UmYLKAMZ2dQqiSHhkAzNm75ztxOXD6FwIfy9vHv
# MxFspsvOnVc5c/78G+dQrKdOAQYGRc8RsrAR7MK03AZmbt8AceHt8ALwY3RHh0Sd
# 5kG7K9TCO/9ExrdtEI3Qi4xOwimPPA5WK8fqUNTyjp3GQTrD7USEqAiZveIKcZdL
# WCei3MnqhrTHeVgy6Ktg6ksWVznjElHVGdwkEqpWoL7a+7fUZFpWYGLBVT9sW5g3
# SjotWcA9Ny7V8wNyfq2zkRtblyGAQwUihQze1IMw1egwhCQxC83dt5mmOcsNvhXw
# 4A0t3mhfP5t36nnNbbW/qh0ZMFRf+qGNLEGFNvBM+qVXX8PH3nH/r/nY+sROrptB
# vq3pMAWrh+ldOZGjy4FWPWmQZWWMk8PG+LoPJoFkQKqUdDCzzAzioNZOT2FMhmsq
# Ur+a8PoneFHvzYcsbpYmIS65VLG/7zOwjzqJs8rrLDCOUGWgfr/5gS1C1LiAjHgP
# /XGc/upV8rsVw+1E7gAcTDaD42bftH7oH5EOKZ7ha9S/FHwXB42MSvLRAa1BW9lw
# Qh+UNevIinZR1AgiBb7OZQ7ZvTlO6WQU8iyJWyBwBg9mN4G7ImR2WFmlh0/Qmlg9
# CJRlNjeGOS6bef/sWcRpWE5X5l1L7RddVrcDuTGCB0Mwggc/AgEBMHgwYTELMAkG
# A1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEyMDAGA1UE
# AxMpTWljcm9zb2Z0IFB1YmxpYyBSU0EgVGltZXN0YW1waW5nIENBIDIwMjACEzMA
# AABLobGt4Vn85zQAAAAAAEswDQYJYIZIAWUDBAIBBQCgggScMBEGCyqGSIb3DQEJ
# EAIPMQIFADAaBgkqhkiG9w0BCQMxDQYLKoZIhvcNAQkQAQQwHAYJKoZIhvcNAQkF
# MQ8XDTI1MDIxMTE5MTI0MlowLwYJKoZIhvcNAQkEMSIEIBYnTAAaaMaSFVyPuN8B
# LnbatwjxpH2cjvOXzQo0d5U3MIG5BgsqhkiG9w0BCRACLzGBqTCBpjCBozCBoAQg
# 24konSuy9FxJybjChmYIqjAxJOH0NabQ5I0B5QAGRKcwfDBlpGMwYTELMAkGA1UE
# BhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEyMDAGA1UEAxMp
# TWljcm9zb2Z0IFB1YmxpYyBSU0EgVGltZXN0YW1waW5nIENBIDIwMjACEzMAAABL
# obGt4Vn85zQAAAAAAEswggNeBgsqhkiG9w0BCRACEjGCA00wggNJoYIDRTCCA0Ew
# ggIpAgEBMIIBCaGB4aSB3jCB2zELMAkGA1UEBhMCVVMxEzARBgNVBAgTCldhc2hp
# bmd0b24xEDAOBgNVBAcTB1JlZG1vbmQxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jw
# b3JhdGlvbjElMCMGA1UECxMcTWljcm9zb2Z0IEFtZXJpY2EgT3BlcmF0aW9uczEn
# MCUGA1UECxMeblNoaWVsZCBUU1MgRVNOOjdEMDAtMDVFMC1EOTQ3MTUwMwYDVQQD
# EyxNaWNyb3NvZnQgUHVibGljIFJTQSBUaW1lIFN0YW1waW5nIEF1dGhvcml0eaIj
# CgEBMAcGBSsOAwIaAxUA9XrCzpvkU0dQ6YQgsANWDOqXmTOgZzBlpGMwYTELMAkG
# A1UEBhMCVVMxHjAcBgNVBAoTFU1pY3Jvc29mdCBDb3Jwb3JhdGlvbjEyMDAGA1UE
# AxMpTWljcm9zb2Z0IFB1YmxpYyBSU0EgVGltZXN0YW1waW5nIENBIDIwMjAwDQYJ
# KoZIhvcNAQELBQACBQDrVbDsMCIYDzIwMjUwMjExMTEyMDEyWhgPMjAyNTAyMTIx
# MTIwMTJaMHQwOgYKKwYBBAGEWQoEATEsMCowCgIFAOtVsOwCAQAwBwIBAAICO4Iw
# BwIBAAICEngwCgIFAOtXAmwCAQAwNgYKKwYBBAGEWQoEAjEoMCYwDAYKKwYBBAGE
# WQoDAqAKMAgCAQACAwehIKEKMAgCAQACAwGGoDANBgkqhkiG9w0BAQsFAAOCAQEA
# blXLQpVUx0cXQJD7PUAEm0la/MgkMUDqLcb1zli9agFghJgpTEBb77A0LkbgmWCK
# PoWLedD4UhpOGahE4e4LoK0jL+ZcIi2ZBUlEuqwFpEjU0RYAEkxdUvE1N2e5f2kF
# m0WsX60R7DkuFdn9VFiS6SgITIALHkmKtSJ4gnXSiiHTLw8AZpQa2nRmhQn3HAYD
# nSpQJ0k/GJw8rSVqI29y3OtDFuxDAR4scInGXBB6Ttb1h9R+EDzKlyA3K2KbYCB/
# j7Qwh7p4FwfjvvsNAeg8IKELKtbSIWPVCRDSThzsBQyfdN2zeiPOShrlkt4trj5/
# kZTPDpUoMVS3HEz7Fj+TzjANBgkqhkiG9w0BAQEFAASCAgBAqfhQ/ZXV3GxdYvWz
# QZF/cje7VJWDpxqUWsoLjh8RBLl6mJi5/SmPHpP5pEul6LnTLx1TNuIrDJXUmxTs
# tWcY5Bcs8p6rixdEV2iNG5iVSzw7I3eX7bmZS7dQGpLVDBibXx6s2gx6/5uOS2X+
# 7hM0V3dFJ/RhVH81h2/tLMJrgbuOkdVwxCer2EOnGoCZFZ+I4PO7Soagt+/dwNWg
# q32g3/OyT/kIDIKpskOj/i00I6MbAYEwPjlFTWcbs/tn2bbmf/kpLlYSreAyH4gB
# MksQK/6y7uzyTgRWNoM5v0SMoMnJEMboxO/7PXSmjbtdevKuuvPi/gfgWNLZhmvS
# T0UROknTrGGpuiR9k2e1WJzdNC+uYJMaItZV+g97nzj8zf3+0UFqPDc4DdE1NS0H
# j1oiEjf9Iw3eca2ZsOSfn8jOe1pgFo+NuPzFbjSQUBAH0cNc40Ub69DSwrcFxsR4
# dUo8JHrEp+4KceSql7oHI9YnPy4CRssu5PoVESl0keCQkX4OETZAVY3Obx+1lypU
# Lai57YNrrrqChG0KAL+U0MXOSV0MO9CnVyUWpOlUS1jFaxwTC96spCaYHNnCGU8Y
# sw+wj6Z9X3dd+kXh//W4Cp71/Ywc7wWqu08MJSkofeKtABFy0SoHiPqe9FupIFGE
# d9IMNZqIp8Z2No320WK0yUC63A==
# SIG # End signature block
