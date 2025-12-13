# Backjoon (학습 저장소)

개인 알고리즘 학습용 저장소입니다. 문제별 소스, 로컬 테스트 스크립트, CI 설정을 포함합니다.

## 목적
- 문제 풀이 연습 및 재현 가능한 로컬 테스트
- PR/커밋 시 자동 빌드·테스트로 안정성 확보

## 디렉터리 구조(주요)
- `dp/`, `graph/`, `dfs_bfs/`, ... : 문제별 소스 파일
- `tests/` : 로컬 테스트 입력/출력(로컬 전용, `.gitignore`에 등록됨)
- `.vscode/` : VS Code 설정 (build/debug)
- `run_tests.ps1`, `run_tests.sh` : 로컬 테스트 러너
- `.github/workflows/` : CI 워크플로

## 빠른 시작 (Windows, MinGW)
1. MinGW가 설치되어 있다고 가정합니다(예: `C:\mingw64`).
2. 현재 파일만 빌드:
```powershell
C:\mingw64\bin\g++.exe -g -O2 -std=c++17 dp\2293.c++ -o dp\2293.exe
```
3. 간단 실행(한 줄 입력):
```powershell
echo 3 10 1 2 5 10 | .\dp\2293.exe
```
4. 테스트 실행(루트에서):
```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\run_tests.ps1 -Exe .\dp\2293.exe -TestsDir .\tests\2293
```

## VS Code 사용법
- Build: `Ctrl+Shift+B` (설정된 `g++: build active file` task 사용)
- Debug: 소스에 브레이크포인트 설정 후 `F5` (launch.json 사용)
- `miDebuggerPath`가 실제 gdb 경로(`C:\mingw64\bin\gdb.exe`)와 일치하는지 확인하세요.

## 테스트 규칙(권장)
- 문제별 하위폴더 방식 추천: `tests/<problem_id>/case1.in`, `case1.out`
- 또는 접두사 방식: `tests/2293_case1.in`, `2293_case1.out`
- 테스트 추가 후 로컬에서 `run_tests.ps1` 또는 `run_tests.sh`로 검증하세요.

## CI (GitHub Actions)
- `.github/workflows/build.yml`는 push/PR 시 Ubuntu와 Windows에서 빌드 및 테스트를 실행합니다.
- PR에서 실패하면 Actions 로그를 확인해 컴파일 에러나 테스트 실패를 조사하세요.

## 학습 팁
- 풀이 파일 상단에 `// BOJ 2293 — 아이디어, 복잡도, 소요시간` 형태로 메모해 두면 복습에 유리합니다.
- 자주 쓰는 컴파일 명령은 `tasks.json`에 등록해 단축키로 사용하세요.

## 주의
- `tests/`는 로컬 테스트용으로 `.gitignore`에 등록되어 있습니다. 원격에 업로드하지 마세요.

---

필요하시면 이 README를 더 개인화(예: 본인 닉네임, 학습 진행표 자동화, PR 템플릿)해 드릴게요.
# 2025.02.20
## 안녕하세요.
저의 첫번째 MD 파일입니다.

깃 허브에 잘 올라갔나요? ㅎㅎ

