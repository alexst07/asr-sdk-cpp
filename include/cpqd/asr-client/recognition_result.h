/*****************************************************************************
 * Copyright 2017 CPqD. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#ifndef INCLUDE_CPQD_ASR_CLIENT_RECOGNITION_RESULT_H_
#define INCLUDE_CPQD_ASR_CLIENT_RECOGNITION_RESULT_H_

#include <string>
#include <vector>

class RecognitionResult {
 public:
  enum class Code {
    PROCESSING,
    RECOGNIZED,
    NO_MATCH,
    NO_INPUT_TIMEOUT,
    MAX_SPEECH,
    EARLY_SPEECH,
    RECOGNITION_TIMEOUT,
    NO_SPEECH,
    CANCELED,
    FAILURE
  };

  class Alternative;

  RecognitionResult();
  
  RecognitionResult(Code result_status);

  RecognitionResult(std::string status_string);
  
  Code getCode() {
    return result_status_;
  }

  std::vector<Alternative> getAlternatives() {
    return alternatives_;
  }

  RecognitionResult& addAlternatives(const Alternative& alt);
  
  static std::string getString(RecognitionResult::Code st);

 private:
  Code result_status_;

  std::vector<Alternative> alternatives_;
};

struct PartialRecognition {
  std::string text_;
  int speech_segment_index_;
};

struct Interpretation {
  std::string text_;
  int confidence_;
};

struct WordConfidence {
  std::string word_;
  int confidence_;
};

struct WordAlignment {
  std::string word_;
  int start_time_;
  int end_time_;
};

class RecognitionResult::Alternative {
 public:
  int getConfidence();
  std::string getText();
  std::vector<Interpretation> getInterpretations();

  RecognitionResult::Alternative& languageModel(std::string lang_model);
  RecognitionResult::Alternative& text(std::string text);
  RecognitionResult::Alternative& addInterpretation(std::string text,
                                            int confidence = 0);
  RecognitionResult::Alternative& confidence(int confidence);

 private:
  std::string lang_model_;
  std::string text_;
  int confidence_ = 0;
  std::vector<Interpretation> interpretations_;
  std::vector<WordConfidence> wordConfidence_;
  std::vector<WordAlignment> wordAlignment_;
};

#endif  // INCLUDE_CPQD_ASR_CLIENT_RECOGNITION_RESULT_H_
