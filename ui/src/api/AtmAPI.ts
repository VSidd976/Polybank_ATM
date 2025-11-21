import type { Card } from "@components/BankCard/consts";
import { useMemoValue } from "@utils/hooks/useMemoValue";
import { useCard } from "@utils/stores/cardStore";
import axios from "axios";
import { useNavigate } from "react-router-dom";
import { toast } from "react-toastify";

export type AccountInfo = {
  balance: number;
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
    return this.api
      .post(`${BASE_URL}/card/accept`, {
        ownerName: this.card.ownerName,
        cardNumber: this.card.number,
        bankName: this.card.bank,
        cvv: this.card.cvv,
        expirationDate: this.card.expDate,
      })
      .catch(() => void 0)
      .then(() => void 0);
  }

  async inputPIN(pin: string): Promise<boolean> {
    console.log("Sending a pin", pin);
    return this.api
      .post(`${BASE_URL}/card/pin`, {
        ownerName: this.card.ownerName,
        cardNumber: this.card.number,
        bankName: this.card.bank,
        cvv: this.card.cvv,
        expirationDate: this.card.expDate,
        pin: pin,
      })
      .catch(() => true)
      .then(() => true);
  }

  async cashOut(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return this.api
      .put(`${BASE_URL}/account/take`, { cash: amount })
      .catch(() => true)
      .then(() => true);
  }

  async putMoney(amount: number): Promise<boolean> {
    console.log({ amount, card: this.card });
    return this.api
      .post(`${BASE_URL}/account/put`, { cash: amount })
      .catch(() => true)
      .then(() => true);
  }

  async transferMoney(amount: number, to: string): Promise<boolean> {
    console.log({ amount, to });
    return this.api
      .post(`${BASE_URL}/account/transfer`, {
        cash: amount,
        number: to,
      })
      .catch(() => true)
      .then(() => true);
  }

  async getInfo(): Promise<AccountInfo> {
    return this.api
      .get(`${BASE_URL}/account/info`)
      .then((r) => ({ balance: r.data.balance }))
      .catch(() => ({ balance: 2 }));
  }

  async endSession(): Promise<void> {
    return this.api
      .put(`${BASE_URL}/card/return`)
      .catch(() => void 0)
      .then(() => void 0);
  }
}

export default AtmAPI;

type ApiOptions = {
  onSuccess?: (data: any) => void;
  onFailure?: (err: any) => void;
};

type StatusOption = { text?: string; redirectTo?: string };

type StatusOptions = {
  sucess?: StatusOption;
  failure?: StatusOption;
} & ApiOptions;

function makeApiOpt(
  navigate: (desination: string) => void,
  opt?: StatusOptions,
): ApiOptions {
  const onSuccess = (data: any) => {
    opt?.sucess?.redirectTo && navigate(opt.sucess.redirectTo);
    opt?.sucess?.text && toast(opt.sucess.text);
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
