param(
    [string]$Exe = "./dp/9252.exe",
    [string]$TestsDir = "./tests"
)

if (-not (Test-Path $TestsDir)) {
    Write-Error "Tests directory '$TestsDir' not found. Create a 'tests' folder with .in/.out files."
    exit 1
}

$inFiles = Get-ChildItem -Path $TestsDir -Filter *.in | Sort-Object Name
if ($inFiles.Count -eq 0) {
    Write-Host "No .in files found in $TestsDir"
    exit 0
}

foreach ($in in $inFiles) {
    $name = $in.BaseName
    Write-Host "=== $name ==="
    $exePath = $Exe
    if (-not (Test-Path $exePath)) {
        Write-Error "Executable '$exePath' not found. Build it first."
        exit 2
    }

    # Run by piping the input file into the exe via cmd to support redirection reliably
    $cmd = 'type "' + $in.FullName + '" | "' + $exePath + '"'
    $outLines = cmd /c $cmd 2>&1
    $out = ($outLines -join "`n").TrimEnd()

    $expectedFile = Join-Path $TestsDir ($name + ".out")
    if (Test-Path $expectedFile) {
        $expected = (Get-Content $expectedFile -Raw).TrimEnd()
        if ($out -eq $expected) {
            Write-Host "PASS`n" -ForegroundColor Green
        } else {
            Write-Host "FAIL" -ForegroundColor Red
            Write-Host "Expected:" -ForegroundColor DarkYellow
            Write-Host $expected
            Write-Host "Actual:" -ForegroundColor DarkYellow
            Write-Host $out
            Write-Host "`n"
        }
    } else {
        Write-Host "Output:" -ForegroundColor Cyan
        Write-Host $out
        Write-Host "`n"
    }
}

Write-Host "All tests finished."
