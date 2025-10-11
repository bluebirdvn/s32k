# Hệ thống Clock, Memory Map, Signal Multiplexing & Core Modules (PORT, GPIO) — S32K1xx

## 1. Tổng quan hệ thống Clock (Clock Distribution)

Hệ thống clock của S32K1xx được thiết kế theo mô hình phân tầng:

```
[Nguồn Clock (SOSC, FIRC, SIRC, SPLL)]
       │
       ▼
  ┌──────────────┐
  │   SCG        │  → Tạo & quản lý clock hệ thống
  └──────────────┘
       │
       ▼
  ┌──────────────┐
  │   PCC        │  → Phân phối clock cho các module
  └──────────────┘
       │
       ▼
  ┌──────────────┐
  │ Peripheral   │  → LPUART, SPI, ADC, FTM…
  └──────────────┘
```

### 1.1 Thành phần chính

* **SCG (System Clock Generator):** tạo và quản lý các nguồn clock hệ thống (System, Core, Bus, Slow).
* **PCC (Peripheral Clock Control):** điều khiển cấp clock cho từng peripheral.
* **CMU (Clock Monitor Unit):** giám sát clock để phát hiện lỗi tần số.

### 1.2 Các loại clock chính

| Clock        | Vai trò                           | Nguồn gốc      |
| ------------ | --------------------------------- | -------------- |
| **CORE_CLK** | cấp cho CPU                       | SCG_DIVCORE    |
| **BUS_CLK**  | cấp cho AIPS & peripheral         | SCG_DIVBUS     |
| **SLOW_CLK** | cho module chậm (watchdog, flash) | SCG_DIVSLOW    |
| **CLKOUT**   | xuất clock ra chân ngoài          | SCG_CLKOUTCNFG |

---

## 2. System Clock Generator (SCG)

### 2.1 Nguồn clock hỗ trợ

| Nguồn    | Tần số   | Ghi chú                       |
| -------- | -------- | ----------------------------- |
| **SIRC** | 8 MHz    | nội, hỗ trợ chế độ VLPS       |
| **FIRC** | 48 MHz   | nội, chính xác cao hơn        |
| **SOSC** | 4–40 MHz | thạch anh ngoài               |
| **SPLL** | 160 MHz  | chỉ có ở S32K14x              |
| **LPO**  | 128 kHz  | dùng cho khối thấp năng lượng |

### 2.2 Cấu trúc SCG

SCG có 3 nhóm thanh ghi chính:

* **CSR (Control Status Register):** bật/tắt nguồn, kiểm tra valid/lock.
* **CFG (Configuration Register):** đặt tần số, range, drive.
* **RCCR/VCCR/HCCR:** chọn nguồn clock hệ thống cho các mode RUN, VLPR, HSRUN.

### 2.3 Quy trình chuyển clock hệ thống (ví dụ sang FIRC)

1. Bật FIRC: `SCG->FIRCCSR |= SCG_FIRCCSR_FIRCEN_MASK;`
2. Chờ valid: `(SCG->FIRCCSR & SCG_FIRCCSR_FIRCVLD_MASK)`
3. Cấu hình divider: `SCG->RCCR = ...`
4. Chọn nguồn: `SCG->RCCR |= SCG_RCCR_SCS(3);`
5. Đọc lại thanh ghi (`read-after-write`) để xác nhận.

---

## 3. Peripheral Clock Control (PCC)

PCC quản lý clock cho từng peripheral thông qua thanh ghi `PCC_<MODULE>`.

### 3.1 Cấu trúc thanh ghi

| Field    | Bit     | Mô tả                                  |
| -------- | ------- | -------------------------------------- |
| **PCS**  | [26:24] | chọn nguồn clock (SOSC, FIRC, SIRC...) |
| **FRAC** | [27]    | hệ số nhân (1 hoặc 2)                  |
| **PCD**  | [30:28] | bộ chia clock                          |
| **CGC**  | [31]    | bật/tắt clock module                   |

### 3.2 Trình tự cấu hình clock cho module

1. **Gate off:** `PCC_<MODULE>.CGC = 0`
2. Cấu hình `PCS`, `FRAC`, `PCD`
3. **Gate on:** `PCC_<MODULE>.CGC = 1`
4. Đọc lại thanh ghi để đảm bảo ghi xong.

### 3.3 Ví dụ cấp clock cho LPUART0

```c
PCC->PCCn[PCC_LPUART0_INDEX] = PCC_PCCn_PCS(3) | PCC_PCCn_CGC_MASK;
(void)PCC->PCCn[PCC_LPUART0_INDEX];
```

---

## 4. Memory Map (Ch.3)

### 4.1 Các vùng nhớ chính

| Vùng                  | Địa chỉ     | Ghi chú                           |
| --------------------- | ----------- | --------------------------------- |
| Flash                 | 0x0000_0000 | bộ nhớ chương trình               |
| SRAM                  | 0x2000_0000 | vùng RAM nội (SRAM_U hoặc SRAM_L) |
| AIPS-Lite Peripherals | 0x4000_0000 | thiết bị ngoại vi                 |
| PPB                   | 0xE000_0000 | vùng đặc quyền Cortex-M4          |

### 4.2 Bit-Banding

Bit-banding ánh xạ từng bit RAM/peripheral thành một từ 32-bit trong vùng alias.

```
Alias = 0x42000000 + ((Addr – 0x40000000) * 32) + (bit * 4)
```

Việc ghi 1 hoặc 0 vào bit 0 của từ alias tương ứng với ghi 1/0 vào bit mục tiêu.

### 4.3 Quy tắc Read-after-Write

Một số thao tác cần đảm bảo việc ghi hoàn tất trước khi bước tiếp theo:

1. Ghi thanh ghi.
2. Đọc lại chính thanh ghi đó.
3. Tiếp tục thao tác khác.

---

## 5. Signal Multiplexing & Pin Assignment (Ch.4)

### 5.1 Chức năng

Mỗi pad có thể được chia sẻ giữa nhiều module (GPIO, LPUART, SPI,...). Bộ **Signal Multiplexing** chịu trách nhiệm chọn tín hiệu nào được nối đến pad.

### 5.2 PORT_PCRn — Pin Control Register

| Field         | Vai trò                                   |
| ------------- | ----------------------------------------- |
| **MUX[10:8]** | chọn chức năng ALT (0–7)                  |
| **PE/PS**     | bật/tắt và chọn kiểu pull                 |
| **SRE/DSE**   | điều chỉnh tốc độ chuyển & drive strength |
| **IRQC/ISF**  | cấu hình ngắt và cờ ngắt                  |

### 5.3 Quy trình cấu hình pad an toàn

1. Thiết lập **pull/slew/drive** trước khi đổi `MUX`.
2. Nếu dùng **analog (ALT0)** → tắt `PE` và `PUS`.
3. Nếu dùng digital filter → tạm tắt `DFER` trước khi đổi `DFCR/DFWR`.
4. Có thể ghi hàng loạt bằng **GPCLR/GPCHR**.

---

## 6. PORT Module (Ch.12)

### 6.1 Vai trò

* Quản lý ngắt cạnh hoặc mức logic.
* Cấu hình input filter (lọc nhiễu tín hiệu digital).
* Cấu hình global pin write.

### 6.2 Thanh ghi chính

| Register                              | Vai trò              |
| ------------------------------------- | -------------------- |
| `PORT_PCRn`                           | cấu hình từng pin    |
| `PORT_GPCLR`, `PORT_GPCHR`            | ghi đồng thời 16 pin |
| `PORT_ISFR`                           | cờ ngắt (W1C)        |
| `PORT_DFER`, `PORT_DFCR`, `PORT_DFWR` | digital filter       |

### 6.3 Digital Filter

* Chọn clock BUS hoặc LPO (`PORT_DFCR[CS]`)
* Độ rộng lọc: 1–32 chu kỳ (`PORT_DFWR[WIDTH]`)
* Chỉ đổi khi tất cả filter disable.

---

## 7. GPIO Module (Ch.13)

### 7.1 Chức năng

GPIO cung cấp thao tác I/O mức logic cho từng port. Mỗi port có 32 chân (tối đa) và bộ thanh ghi riêng.

### 7.2 Thanh ghi chính

| Register                 | Vai trò                            |
| ------------------------ | ---------------------------------- |
| `PDOR`                   | ghi dữ liệu ra                     |
| `PSOR` / `PCOR` / `PTOR` | set / clear / toggle bit           |
| `PDIR`                   | đọc đầu vào                        |
| `PDDR`                   | chọn hướng (1 = output, 0 = input) |

---

## 8. Ví dụ: Blink LED tại PTD0, PTD15, PTD16

### 8.1 Clock hệ thống

Sau reset, SCG mặc định chọn **SIRC (8 MHz)** làm nguồn System Clock.
Các divider mặc định:

| Clock | Nguồn | Tần số |
|--------|--------|---------|
| CORE_CLK | SIRC/1 | 8 MHz |
| BUS_CLK | CORE/2 | 4 MHz |
| SLOW_CLK | CORE/4 | 2 MHz |

Không cần cấu hình lại SCG.

---

### 8.2 PCC — bật clock cho PORTD

```c
PCC->PCCn[PCC_PORTD_INDEX] |= PCC_PCCn_CGC_MASK;
```

Bit **PR=1**: PORTD có trên chip  
Bit **CGC=1**: bật clock interface, cho phép truy cập thanh ghi PORTD

---

### 8.3 PORT — cấu hình pin PTD0, PTD15, PTD16 làm GPIO

#### Sử dụng GPCLR/GPCHR để ghi nhanh:

```c
// PTD0 & PTD15 (PORT_GPCLR)
PORTD->GPCLR = (((1 << 0) | (1 << 15)) << 16) | PORT_PCR_MUX(1);

// PTD16 (PORT_GPCHR)
PORTD->GPCHR = ((1 << (16 - 16)) << 16) | PORT_PCR_MUX(1);
```

**Giải thích:**
- `PORT_PCR_MUX(1)` → ALT1 = GPIO
- `GPWE` (bit [31:16]) → chọn pin cần ghi
- `GPWD` (bit [15:0]) → dữ liệu ghi (MUX=1)

---

### 8.4 GPIO — cấu hình output và blink LED

```c
// Chọn PTD0, PTD15, PTD16 làm output
PTD->PDDR |= (1 << 0) | (1 << 15) | (1 << 16);

// Blink LED
while (1)
{
    PTD->PTOR = (1 << 0) | (1 << 15) | (1 << 16); // Toggle
    for (volatile int i = 0; i < 1000000; i++);   // Delay
}
```

**Giải thích:**
- `PTOR`: write-one-to-toggle
- `PDDR`: xác định hướng output
- `PDOR`: có thể dùng thay cho PSOR/PCOR/PTOR

