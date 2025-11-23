import type { Card } from "@components/BankCard/consts";
import { useMemoValue } from "@utils/hooks/useMemoValue";
import { useCard } from "@utils/stores/cardStore";
import axios from "axios";
import { useNavigate } from "react-router-dom";
import { toast } from "react-toastify";

export type AccountInfo = {
  balance: number;
};

export type DepositResponseDto = {
  startDate: string;
  endDate: string;
  id: string;
  productName: string;
  amount: number;
};

export type DepositProductResponseDto = {
  termMonths: number;
  id: string;
  name: string;
  interestRate: string;
};

export type DepositRequestDto = {
  productId: string;
  amount: number;
};

const BASE_URL = "http://localhost:8000";

class AtmAPI {
  private readonly api = axios.create({
    baseURL: BASE_URL,
  });
  constructor(
    private readonly card: Card,
    opt?: ApiOptions,
  ) {
    this.api.interceptors.response.use(
      (res) => {
        opt?.onSuccess?.(res);
        return res;
      },
      (err) => {
        opt?.onFailure?.(err);
        return Promise.reject(err);
      },
    );
  }

  static of(card: Card, opt?: ApiOptions): AtmAPI {
    return new AtmAPI(card, opt);
  }
  async insertCard(): Promise<void> {
    console.log("INSERTING");
    return this.api.post(`/card/accept`, {
      ownerName: this.card.ownerName,
      cardNumber: this.card.number,
      bankName: this.card.bank,
      cvv: this.card.cvv,
      expirationDate: this.card.expDate,
    });
  }

  async inputPIN(pin: string): Promise<boolean> {
    console.log("Sending a pin", pin);
    return this.api.post(`/card/pin`, {
      ownerName: this.card.ownerName,
      cardNumber: this.card.number,
      bankName: this.card.bank,
      cvv: this.card.cvv,
      expirationDate: this.card.expDate,
      pin: pin,
    });
  }

  async cashOut(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return this.api.put(`/account/take`, { cash: amount });
  }

  async putMoney(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return this.api.post(`/account/put`, { cash: amount });
  }

  async transferMoney(amount: number, to: string): Promise<boolean> {
    console.log({ amount, to });
    return this.api.post(`/account/transfer`, {
      cash: amount,
      number: to,
    });
  }

  async getInfo(): Promise<AccountInfo> {
    return this.api
      .get(`/account/info`)
      .then((r) => ({ balance: r.data.balance }));
  }

  async getAllDeposits(): Promise<DepositResponseDto[]> {
    return this.api.get(`/deposit`).then((r) => r.data);
  }

  async depositProducts(): Promise<DepositProductResponseDto[]> {
    return this.api.get(`/product`).then((r) => r.data);
  }

  async newDeposit(deposit: DepositRequestDto): Promise<void> {
    return this.api.post(`/deposit`, deposit);
  }

  async endSession(): Promise<void> {
    return this.api.put(`/card/return`);
  }
}

export default AtmAPI;

type ApiOptions = {
  onSuccess?: (data: any) => void;
  onFailure?: (err: any) => void;
};

type StatusOption = { text?: string; redirectTo?: string };

type StatusOptions = {
  success?: StatusOption;
  failure?: StatusOption;
} & ApiOptions;

function makeApiOpt(
  navigate: (desination: string) => void,
  opt?: StatusOptions,
): ApiOptions {
  const onSuccess = (data: any) => {
    opt?.success?.redirectTo && navigate(opt.success.redirectTo);
    opt?.success?.text && toast(opt.success.text);
    opt?.onSuccess?.(data);
  };

  const onFailure = (err: any) => {
    console.log("HERE");
    opt?.failure?.redirectTo && navigate(opt.failure.redirectTo);
    opt?.failure?.text && toast.error(opt.failure.text);
    opt?.onFailure?.(err);
  };
  return { onSuccess, onFailure };
}

export const useAtmApi = (opt?: StatusOptions): AtmAPI | null => {
  const { card } = useCard();
  const navigate = useNavigate();
  const api = useMemoValue(
    (_card, _opt, redirect) => {
      if (!_card) return null;
      return AtmAPI.of(_card, makeApiOpt(redirect, _opt));
    },
    [card, opt, navigate],
  );
  return api;
};
