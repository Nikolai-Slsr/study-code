# Code Review for PR #5: Lab 6 - Sensor Fusion

## Summary
This PR adds a Lab 6 solution implementing sensor fusion for object detection. The code includes:
- 3 files: `sensorfusion.c`, `sensor1.txt`, `sensor2.txt`
- 149 lines of C code for sensor data processing
- 6000 lines of sensor data (3000 per file)

## Critical Issues

### 1. **Typo in struct field name** (Line 7)
- **Issue**: `probablity` should be `probability`
- **Location**: `struct SensorData` line 7 and used throughout the code (lines 52, 88, 123)
- **Impact**: This is a consistent misspelling that affects readability and professionalism
- **Severity**: Medium (works but unprofessional)

### 2. **Missing file closure** (Line 55)
- **Issue**: `importSensorData()` opens files but never calls `fclose()`
- **Location**: After the `while` loop in `importSensorData()` function
- **Impact**: Resource leak - file handles are never released
- **Severity**: High (memory/resource leak)

### 3. **Incomplete sensor fusion implementation**
- **Issue**: The `sensorFusion()` function is defined but **never called** in `main()`
- **Location**: Function at lines 98-105, missing call in main
- **Impact**: Lab requirement #4 (overlapping intervals) is not fulfilled
- **Severity**: High (missing requirement)

### 4. **Missing output for fused detections**
- **Issue**: No output showing overlapping/fused detections between sensors
- **Location**: main() function
- **Impact**: Lab requirement to "Output all intervals... Overlapping detections (fusion)" is not met
- **Severity**: High (missing requirement)

### 5. **Threshold comparison operator**
- **Issue**: Uses `>=` but requirement states "1 if probability > threshold" (strictly greater than)
- **Location**: Line 88 in `generateDetectionSignal()`
- **Impact**: Edge case behavior differs from specification
- **Severity**: Low (minor specification deviation)

## Quality Issues

### 6. **Missing Section I and Section II implementations**
- **Issue**: The PR only includes Section III (sensor fusion), missing:
  - Section I: File I/O function demonstrations (fgetc, fgets, fscanf, etc.)
  - Section II: Car struct with refuel() function
- **Impact**: Lab is incomplete
- **Severity**: High (missing requirements)

### 7. **Inconsistent variable naming conventions**
- **Issue**: Mix of camelCase (`currentLine`, `trailingIndex`) and PascalCase (`Index`, `Sensor`)
- **Location**: Throughout the code
- **Impact**: Reduces code readability
- **Severity**: Low (style issue)

### 8. **Unused variable `rest`**
- **Issue**: Variable `rest` is declared but not meaningfully used
- **Location**: Lines 47, 49-50
- **Impact**: Compiler warning, unnecessary code
- **Severity**: Low (cleanup needed)

### 9. **Missing error handling for `fclose()`**
- **Issue**: When file operations complete, no explicit file closure
- **Location**: `importSensorData()` function
- **Impact**: Resource management
- **Severity**: Medium

### 10. **Magic numbers**
- **Issue**: Hard-coded values like 3000, 100 without named constants
- **Location**: Throughout the code (lines 23, 41, etc.)
- **Impact**: Reduces maintainability
- **Severity**: Low (style/maintainability)

## Design Observations

### 11. **Function return values not checked**
- **Issue**: `importSensorData()` returns error codes but they're not checked in `main()`
- **Location**: Lines 133, 139
- **Impact**: Silent failures possible
- **Severity**: Medium

### 12. **Inefficient struct return**
- **Issue**: `sensorFusion()` returns entire Sensor struct by value (large copy)
- **Location**: Line 98
- **Impact**: Performance - copying large structs is expensive
- **Severity**: Low (works but inefficient)

### 13. **Incorrect sizeof usage**
- **Issue**: Line 83: `sizeof(Sensor->data)` when Sensor is a pointer gives wrong result
- **Location**: `generateDetectionSignal()` function
- **Impact**: Would work here because of pointer arithmetic, but conceptually wrong
- **Severity**: Low (works by accident)

### 14. **Print formatting issues**
- **Issue**: Line 113: `%1d` should be `%d` (the 1 is unnecessary)
- **Location**: `printSingleDetectionIntervals()` function
- **Impact**: Minor display formatting
- **Severity**: Very Low

### 15. **Missing newline at end of file**
- **Issue**: File ends without newline character
- **Location**: Last line (149)
- **Impact**: Some compilers/tools may warn
- **Severity**: Very Low

## Requirements Compliance

| Requirement | Status | Notes |
|------------|--------|-------|
| Section I: File I/O functions | ❌ Missing | Not implemented |
| Section II: Car struct & refuel() | ❌ Missing | Not implemented |
| Section III: Data Structures | ✅ Partial | Implemented but with typo |
| Read measurement files | ✅ Done | Works correctly |
| Binary detection signal | ✅ Done | Works (minor operator issue) |
| Detection intervals per sensor | ✅ Done | Correctly implemented |
| Overlapping intervals (fusion) | ❌ Missing | Function exists but not called |
| Output all intervals | ⚠️ Partial | Individual sensors yes, fusion no |

## Recommendations

### High Priority Fixes:
1. Fix the typo: `probablity` → `probability`
2. Add `fclose(sensorData);` before returning in `importSensorData()`
3. Call `sensorFusion()` in main and print the results
4. Add Section I and Section II implementations
5. Check return values from `importSensorData()`

### Medium Priority Improvements:
6. Change `>=` to `>` in threshold comparison (line 88)
7. Use consistent naming conventions (prefer snake_case or camelCase)
8. Add error handling for file operations

### Low Priority Enhancements:
9. Replace magic numbers with named constants (#define)
10. Remove unused `rest` variable or use it to check for parsing errors
11. Consider passing pointers instead of returning large structs
12. Add comments explaining the logic
13. Fix `%1d` to `%d` in printf

## Positive Aspects

1. ✅ Code structure is logical and well-organized
2. ✅ Detection interval algorithm is correctly implemented
3. ✅ Edge case handling (detection ending at last index) is present
4. ✅ Sensor struct design is reasonable and meets most requirements
5. ✅ Bitwise AND for fusion logic is appropriate
6. ✅ File reading logic is functional

## Overall Assessment

**Status**: Needs significant work before merging

**Strengths**:
- Core logic for detection intervals is sound
- Good use of structs
- File I/O is functional

**Weaknesses**:
- Missing 2/3 of the lab requirements (Sections I & II)
- Critical typo throughout the code
- Resource leak (missing fclose)
- Sensor fusion implemented but not used
- No output for fused detection intervals

**Recommendation**: Request changes. The code shows good understanding of the problem but needs:
1. Complete implementation of all three sections
2. Fix critical issues (typo, resource leak, call sensor fusion)
3. Add complete output including fused intervals
